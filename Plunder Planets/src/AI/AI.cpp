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


	math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
	playerDir.Normalize();
	float pDotR = playerDir.Dot(norRight);
	float pDotF = playerDir.Dot(norFor);
		/*Right forward and no island on rigth*/		/*Right back and no island on right*/
	if ((((pDotR > 0.0 && pDotF > 0.0 || pDotR > 0.1 && pDotF < 0.0) && !objectLeft) || pDotF <= -0.9 && objectFront) || objectFront && objectLeft)	//Turn right
		return 1;
			/*Left forward and no island on left*/			/*Left back and no island on left*/
	else if ((((pDotR < 0.0 && pDotF > 0.0 || pDotR < -0.1 && pDotF < 0.0) && !objectRight) || pDotF <= -0.9 && objectFront) || objectFront && objectRight)		//Turn left
		return -1;
			/*Cone forward and no island forward*/
	else if (pDotF <= -0.9 && !objectFront)	//Continue forward
		return 0;
	else
		return 0;




	switch (m_state)
	{
	case Behavior::Attacking:
	{
		break;
	}
	case Behavior::Fiering:
	{
		break;
	}
	case Behavior::Idle:
	{
		break;
	}
	case Behavior::Searching:
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
	if (math::Vector3::DistanceSquared(pos, m_playerShip->m_transform->GetPosition()) <= radius * radius)
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

void AI::InsideAttackRadius(float radius, math::Vector3 pos, math::Vector3 & dir)
{
	if (math::Vector3::DistanceSquared(pos, m_playerShip->m_transform->GetPosition()) <= radius * radius)
	{
		dir = m_playerShip->m_transform->Forward();		//Should maby bee (-m_playerShip->m_transform->Forward())
		m_state = Behavior::Fiering;
	}
}

AI::Behavior AI::GetState()
{
	return m_state;
}
