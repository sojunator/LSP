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
		float pDotR = playerDir.Dot(norRight);
		float pDotF = playerDir.Dot(norFor);

		/*Right forward and no island on rigth*/		/*Right back and no island on right*/
		if (pDotR >= 0.0 && pDotF >= 0.0 || pDotR >= 0.1 && pDotF <= 0.0 && !objectLeft || pDotF <= -0.9 && objectFront || objectFront && objectLeft)	//Turn right
			return 1;
		/*Left forward and no island on left*/			/*Left back and no island on left*/
		else if (pDotR < 0.0 && pDotF > 0.0 || pDotR < -0.1 && pDotF < 0.0 && !objectRight || pDotF <= -0.9 && objectFront || objectFront && objectRight)		//Turn left
			return -1;
		/*Cone forward and no island forward*/
		else if (pDotF <= -0.9 && !objectFront)	//Continue forward
			return 0;
		else
			return 0;
		break;
	}
	case Behavior::Firing:
	{
		math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
		playerDir.Normalize();
		float pDotR = playerDir.Dot(norRight);
		float pDotF = playerDir.Dot(norFor);
		/*Change to 0.9*/
		if ((pDotR >= 0.55 || pDotR <= -0.55) && !objectFront)
			return 0;
		else if (objectRight || objectFront || objectRight && objectFront || pDotR < 0.55 && pDotF > 0.0 || pDotR < 0.0 && pDotF > -0.55)
			return -1;
		else if (objectLeft || objectFront && objectLeft || pDotR < 0.55 && pDotF > -1.0 || pDotR < 0.0 && pDotF > 0.55)
			return 1;
		else
			return 0;

		break;
	}
	case Behavior::Idle:
	{
		break;
	}
	case Behavior::Searching:
	{
		math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - m_lastKnownPos;
		playerDir.Normalize();
		float pDotR = playerDir.Dot(norRight);
		float pDotF = playerDir.Dot(norFor);

		/*Right forward and no island on rigth*/		/*Right back and no island on right*/
		if (pDotR > 0.0 && pDotF > 0.0 || pDotR > 0.1 && pDotF < 0.0 && !objectLeft || pDotF <= -0.9 && objectFront || objectFront && objectLeft)	//Turn right
			return 1;
		/*Left forward and no island on left*/			/*Left back and no island on left*/
		else if (pDotR < 0.0 && pDotF > 0.0 || pDotR < -0.1 && pDotF < 0.0 && !objectRight || pDotF <= -0.9 && objectFront || objectFront && objectRight)		//Turn left
			return -1;
		/*Cone forward and no island forward*/
		else if (pDotF <= -0.9 && !objectFront)	//Continue forward
			return 0;
		else
			return 0;
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
		dir = -m_playerShip->m_transform->Forward();		//Should maby be (-m_playerShip->m_transform->Forward())
		m_state = Behavior::Firing;
	}
}

void AI::MatchSpeed(float& speed, float acceleration, float retardation)
{
	if (speed <= m_playerShip->GetSpeed())
		speed += acceleration * Time::GetDeltaTime();
	 /*
	else
		speed -= retardation * Time::GetDeltaTime();
	*/
}

AI::Behavior AI::GetState()
{
	return m_state;
}
