#include "AI.h"
#include "../../THOMAS/src/utils/DebugTools.h"

AI::AI() : thomas::object::component::Component("AI")
{
	m_terrainObject = (TerrainObject*)thomas::object::GameObject::Find("TerrainObject");
	m_playerShip = (Ship*)thomas::object::GameObject::Find("Ship");

	m_state = Behavior::Idle;
	m_stateStr = "Searching";

	m_lastKnownPos = math::Vector3::Zero;
	m_escapeTimer = 0;
	m_escapeTime = 100;	//Should be 10 seconds

	thomas::utils::DebugTools::AddFloatWithStep(pDotR, "pDotR", "min=0.0 max=1.0 step=0.001");
	thomas::utils::DebugTools::AddFloatWithStep(pDotF, "pDotF", "min=0.0 max=1.0 step=0.001");
	thomas::utils::DebugTools::AddString(m_stateStr, "State");
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
	/**
	* 1 is right
	* -1 is left
	* 0 is forward
	*/
	switch (m_state)
	{
	case Behavior::Attacking:
	{
		math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
		playerDir.Normalize();
		pDotR = playerDir.Dot(norRight);
		pDotF = playerDir.Dot(norFor);

		if (pDotF >= 0.8 && pDotR >= -0.2 && pDotR <= 0.2 && !objectFront)	//Continue forward
			return 0;
		/*Left forward and no island on left*/			/*Left back and no island on left*/
		else if (pDotR < 0.0 && pDotF < 0.0 || pDotR <= -0.2 && pDotF >= 0.0 && !objectRight || pDotF >= 0.8 && objectFront || objectFront && objectLeft)
			return 1;
		/*Right forward and no island on rigth*/		/*Right back and no island on right*/
		else if (pDotR >= 0.0 && pDotF <= 0.0 || pDotR >= 0.2 && pDotF >= 0.0 && !objectLeft || objectFront && objectRight)
			return -1;
		/*Cone forward and no island forward*/
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

		if (((pDotR >= 0.98 || pDotR <= -0.98) && !objectFront) || objectLeft && objectRight && !objectFront)
			return 0;
		else if (((pDotR <= 0.98 && pDotF > 0.0 || pDotR < 0.0 && pDotF >= -0.98) && (!objectRight || objectFront || objectLeft && objectFront)) || objectLeft && objectFront)
			return 1;
		else if (((pDotR <= 0.98 && pDotF > -1.0 || pDotR < 0.0 && pDotF >= 0.98) && (!objectLeft || objectFront && objectRight)) || objectFront && objectRight)
			return -1;
		else
			return 0;

		break;
	}
	case Behavior::Idle:
	{
		if (!objectFront || objectLeft && objectRight && !objectFront)
			return 0;
		//else if(objectLeft && )
		break;
	}
	case Behavior::Searching:
	{
		math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - m_lastKnownPos;
		playerDir.Normalize();
		float pDotR = playerDir.Dot(norRight);
		float pDotF = playerDir.Dot(norFor);

		if (pDotF >= 0.8 && pDotR >= -0.2 && pDotR <= 0.2 && !objectFront)	//Continue forward
			return 0;
		/*Left forward and no island on left*/			/*Left back and no island on left*/
		else if (pDotR < 0.0 && pDotF < 0.0 || pDotR <= -0.2 && pDotF >= 0.0 && !objectRight || pDotF >= 0.8 && objectFront || objectFront && objectLeft)
			return 1;
		/*Right forward and no island on rigth*/		/*Right back and no island on right*/
		else if (pDotR >= 0.0 && pDotF <= 0.0 || pDotR >= 0.2 && pDotF >= 0.0 && !objectLeft || objectFront && objectRight)
			return -1;
		/*Cone forward and no island forward*/
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
		m_stateStr = "Attacking";
		m_state = Behavior::Attacking;
	}
	else if (m_state == Behavior::Attacking || m_state == Behavior::Firing)
	{
		m_lastKnownPos = m_playerShip->m_transform->GetPosition();
		m_escapeTimer += Time::GetDeltaTime();
		m_stateStr = "Searching";
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
		m_stateStr = "Firing";
		m_state = Behavior::Firing;
	}
}

void AI::MatchSpeed(float& speed, float acceleration, float retardation)
{
	/*if (speed <= m_playerShip->GetSpeed())
		speed += acceleration * Time::GetDeltaTime();*/
	 /*
	else
		speed -= retardation * Time::GetDeltaTime();
	*/
}

AI::Behavior AI::GetState()
{
	return m_state;
}
