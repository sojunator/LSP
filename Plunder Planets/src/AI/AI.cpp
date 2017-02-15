#include "AI.h"

AI::AI()
{
	m_terrainObject = (TerrainObject*)thomas::object::GameObject::Find("TerrainObject");
	m_playerShip = (Ship*)thomas::object::GameObject::Find("Ship");
	m_pathfinding = new Pathfinding;

	m_state = Behavior::Idle;

	m_lastKnownPos = math::Vector3::Zero;
	m_escapeTimer = 0;
	m_escapeTime = 100;	//Should be 10 seconds
}

AI::~AI()
{
	delete m_pathfinding;
}

bool AI::CheckInFront(math::Vector3 pos)
{
	if (m_terrainObject->Collision(pos))
	{
		return true;
	}
	return false;
}

bool AI::CheckSide(math::Vector3 pos)
{
	if (m_terrainObject->Collision(pos))
	{
		return true;
	}
	return false;
}

int AI::TurnDir(math::Vector3 pos, math::Vector3 right)
{
	math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
	if (playerDir.Dot(right) == 0)		//Continue forward
		return 0;
	else if (playerDir.Dot(right) < 0)	//Turn left
		return -1;
	else								//Turn right
		return 1;
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
	if (math::Vector3::DistanceSquared(pos, m_playerShip->m_transform->GetPosition()))
	{
		m_escapeTimer = 0;
		dir = m_playerShip->m_transform->GetPosition();
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
