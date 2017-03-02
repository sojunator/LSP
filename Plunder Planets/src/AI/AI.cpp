#include "AI.h"
#include "../../THOMAS/src/utils/DebugTools.h"
#include "../gameobjects/TerrainObject.h"

AI::AI() : thomas::object::component::Component("AI")
{
	m_terrainObject = (TerrainObject*)thomas::object::GameObject::Find("TerrainObject");
	m_playerShip = thomas::object::GameObject::Find("Ship");
	m_enemies = thomas::object::GameObject::FindAllOfType("Enemy");

	m_stateStr = "Attacking";			//Should be Idle on start
	m_state = Behavior::Attacking;		//Should be Idle on start

	m_lastKnownPos = math::Vector3::Zero;
	m_escapeTimer = 0;
	m_escapeTime = 600;	//Should be 60 seconds?
	m_idleTimer = 0;
	m_idleTime = 30;

	thomas::utils::DebugTools::AddFloatWithStep(pDotF, "pDotF", "min=0 max=10 step=0.01");
	thomas::utils::DebugTools::AddFloatWithStep(pDotR, "pDotR", "min=0 max=10 step=0.01");
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
	//float pDotR;
	//float pDotF;
	pDotR = 0;
	pDotF = 0;
	float eDotR = 0;
	float eDotF = 0;
	int turnDir = 0;
	/**
	* 1 is right
	* -1 is left
	* 0 is forward
	*/

	int avoidEnemy = 0;
	int avoidIsland = 0;
	int goToPlayer = 0;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		float distance = math::Vector3::Distance(m_enemies[i]->m_transform->GetPosition(), pos);
		if (distance <= 200)
		{
			eDotF = (m_enemies[i]->m_transform->GetPosition() - pos).Dot(forward);
			if (eDotF >= 0.8)
				avoidEnemy = 1;
		}
	}

	if (objectFront && objectLeft)
		avoidIsland = 1;
	else if (objectFront && objectRight)
		avoidIsland = -1;
	else if (objectFront)
		avoidIsland = 1;
	else if (objectLeft)
		avoidIsland = 1;
	else if (objectRight)
		avoidIsland = -1;

	pDotR = (m_playerShip->m_transform->GetPosition() - pos).Dot(right);
	pDotF = (m_playerShip->m_transform->GetPosition() - pos).Dot(forward);
	if (pDotR >= 0.0)
		goToPlayer = 1;
	if (pDotR <= 0.0)
		goToPlayer = -1;

	if (avoidIsland != 0)
		return avoidIsland;
	else if (avoidEnemy != 0)
		return avoidEnemy;
	else if (goToPlayer != 0)
		return goToPlayer;


}

int AI::FireCannons(math::Vector3 pos, math::Vector3 right)
{
	if (m_idleTimer >= m_idleTime)
	{
		right.Normalize();
		math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
		playerDir.Normalize();
		float pDotR = playerDir.Dot(right);

		if (pDotR >= 0.9)
			return 1;
		else if (pDotR <= -0.9)
			return -1;
		else
			return 0;
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
		dir = -m_playerShip->m_transform->Forward();
		m_stateStr = "Firing";
		m_state = Behavior::Firing;
	}
}

AI::Behavior AI::GetState()
{
	return m_state;
}

void AI::Escape()
{
	if (m_escapeTimer >= m_escapeTime)
	{
		m_stateStr = "Idle";
		m_state = Behavior::Idle;
	}
}

math::Vector3 AI::GetTargetPos()
{
	return m_playerShip->m_transform->GetPosition();
}

void AI::IdleTimer()
{
	m_idleTimer += Time::GetDeltaTime();
}

