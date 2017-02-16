#include "AI.h"

AI::AI() : thomas::object::component::Component("AI")
{
	m_terrainObject = (TerrainObject*)thomas::object::GameObject::Find("TerrainObject");
	m_playerShip = (Ship*)thomas::object::GameObject::Find("Ship");

	m_state = Behavior::Idle;

	m_lastKnownPos = math::Vector3::Zero;
	m_escapeTimer = 0;
	m_escapeTime = 100;	//Should be 10 seconds
}

AI::~AI()
{
}

bool AI::Collision(math::Vector3 pos)
{
	if (m_terrainObject->Collision(pos))
	{
		return true;
	}
	return false;
}

int AI::TurnDir(math::Vector3 pos, math::Vector3 forward, math::Vector3 right, bool objectFront, bool objectRight, bool objectLeft)
{
	math::Vector3 norFor = forward;
	norFor.Normalize();
	math::Vector3 norRight = right;
	norRight.Normalize();

	switch (m_state)
	{
	case Behavior::Attacking:
	{
		math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
		playerDir.Normalize();
		if (playerDir.Dot(norRight) <= 0.1 && playerDir.Dot(norRight) >= -0.1 && !objectFront && playerDir.Dot(norFor) < -0.9 /*|| objectLeft && objectRight*/)		//Continue forward
			return 0;
		else if (playerDir.Dot(norRight) < -0.1 && !objectLeft /*|| objectFront && objectRight*/ || playerDir.Dot(right) <= 0.1 && playerDir.Dot(right) >= -0.1 && objectFront)	//Turn left
			return -1;
		else if (playerDir.Dot(norRight) > 0.1 && !objectRight/* || objectFront && objectLeft*/)			//Turn right
			return 1;
		else
			return 1;
		break;
	}
	case Behavior::Searching:
	{
		math::Vector3 playerDir = m_lastKnownPos - pos;
		playerDir.Normalize();
		if (playerDir.Dot(norRight) <= 0.1 && playerDir.Dot(norRight) >= -0.1 && !objectFront && playerDir.Dot(norFor) < -0.9 || objectLeft && objectRight)		//Continue forward
			return 0;
		else if (playerDir.Dot(norRight) < -0.1 && !objectLeft || objectFront && objectRight || playerDir.Dot(right) <= 0.1 && playerDir.Dot(right) >= -0.1 && objectFront)	//Turn left
			return -1;
		else if (playerDir.Dot(norRight) > 0.1 && !objectRight || objectFront && objectLeft)			//Turn right
			return 1;
		else
			return 1;
		break;
		break;
	}
	case Behavior::Idle:
	{
		break;
	}
	default:
		break;
	}

}

float AI::Move(math::Vector3 pos, float speed, float retardation, float acceleration)
{
	if (math::Vector3::DistanceSquared(m_playerShip->m_transform->GetPosition(), pos) < 200 * 200)
	{
		speed -= retardation * Time::GetDeltaTime();
		speed = std::fminf(speed, 0);
		return speed;
	}
	else
	{
		return speed += acceleration * Time::GetDeltaTime();
	}
}

void AI::InsideRadius(float radius, math::Vector3 pos, math::Vector3& dir)
{
	if (math::Vector3::DistanceSquared(pos, m_playerShip->m_transform->GetPosition()) < radius * radius)
	{
		m_escapeTimer = 0;
		dir = m_playerShip->m_transform->GetPosition() - pos;
		m_state = Behavior::Attacking;
	}
	else if (m_state == Behavior::Attacking)
	{
		m_lastKnownPos = m_playerShip->m_transform->GetPosition();
		m_escapeTimer += Time::GetDeltaTime();
		m_state = Behavior::Searching;
	}
	else
	{
		m_escapeTimer += Time::GetDeltaTime();
	}
	
}

AI::Behavior AI::GetState()
{
	return m_state;
}
