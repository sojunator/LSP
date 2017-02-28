#include "AI.h"
#include "../../THOMAS/src/utils/DebugTools.h"
#include "../gameobjects/TerrainObject.h"

AI::AI() : thomas::object::component::Component("AI")
{
	m_terrainObject = (TerrainObject*)thomas::object::GameObject::Find("TerrainObject");
	m_playerShip = thomas::object::GameObject::Find("Ship");
	m_enemies = thomas::object::GameObject::FindAllOfType("Enemy");

	m_state = Behavior::Searching;		//Should be Idle on start
	m_stateStr = "Searching";			//Should be Idle on start

	m_lastKnownPos = math::Vector3::Zero;
	m_escapeTimer = 0;
	m_escapeTime = 600;	//Should be 60 seconds?
	m_idleTimer = 0;
	m_idleTime = 50;
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
	float eDotR;
	float eDotF;
	math::Vector3 norFor = forward;
	norFor.Normalize();
	math::Vector3 norRight = right;
	norRight.Normalize();
	int turnDir = 0;
	/**
	* 1 is right
	* -1 is left
	* 0 is forward
	*/
	//First check with other enemies
	for (unsigned int i = 0; i < m_enemies.size(); ++i)
	{
		float distance = math::Vector3::Distance(pos, m_enemies[i]->m_transform->GetPosition());
		if (distance <= 50 && distance != 0)
		{
			math::Vector3 enemyDir = m_enemies[i]->m_transform->GetPosition() - pos;
			enemyDir.Normalize();
			float fEnemyDir = enemyDir.Dot(norRight);

			math::Vector3 enemyForward = -m_enemies[i]->m_transform->Forward();
			enemyForward.Normalize();
			eDotR = enemyForward.Dot(right);
			eDotF = enemyForward.Dot(forward);
			if (fEnemyDir >= 0.0)	//Right side
			{
				if (eDotF >= 0.0 && eDotR <= 0.0)	//Turn left
					turnDir = -1;
			}
			else	//Left side
			{
				if (eDotF >= 0.0 && eDotR > 0.0)	//Turn right
					turnDir = 1;
			}
		}
	}

	math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
	playerDir.Normalize();
	pDotR = playerDir.Dot(norRight);
	pDotF = playerDir.Dot(norFor);

	if (!objectFront && !objectLeft && !objectRight) //Follow player, no islands near
	{
		if (turnDir == 0)	//No other enemies near
		{
			if (pDotF >= 0.9)	//Forward
				return 0;
			else if ((pDotR >= 0.1 && pDotF >= 0.0) || (pDotR >= 0.0 && pDotF <= 0.0))	//Turn right
				return 1;
			else if ((pDotR <= -0.1 && pDotF >= 0.0) || (pDotR <= 0.0 && pDotF <= 0.0))	//Turn left
				return -1;
		}
		else if (turnDir == 1)	//Turn right
			return 1;	//Turn right
		else if (turnDir == -1)
			return -1;
	}
	else if (turnDir == 0)	//Forward
	{
		if (!objectFront)	//Forward
		{
			if (pDotF >= 0.9)	//Forward
			{
				return 0;
			}
		}
		else if (objectFront)	//Turn
		{
			if (pDotR < 0.0)	//Turn left
			{
				if (!objectLeft)	//Turn left
				{
					return -1;
				}
				else	//Turn right
				{
					return 1;
				}
			}
			else	//Turn right
			{
				if (!objectRight)	//Turn right
				{
					return 1;
				}
				else	//Turn left
				{
					return -1;
				}
			}
		}
	}
	else if (turnDir == 1)	//Turn right, boat to the left. Avoid turn left.
	{
		if (!objectRight)	//Turn right
			return 1;
		else if (objectRight)	//Forward
			return 0;
	}
	else if (turnDir == -1)	//Turn left, boat to the right. Avoid turn right.
	{
		if (!objectLeft)	//Turn left
			return -1;
		else if (objectLeft)	//Forward
			return 0;
	}





















	
	//switch (m_state)
	//{
	//case Behavior::Attacking:
	//{
	//	math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
	//	playerDir.Normalize();
	//	pDotR = playerDir.Dot(norRight);
	//	pDotF = playerDir.Dot(norFor);

	//	if (pDotF >= 0.8 && pDotR >= -0.2 && pDotR <= 0.2 && !objectFront)	//Continue forward
	//		return 0;
	//	/*Left forward and no island on left*/			/*Left back and no island on left*/
	//	else if (pDotR < 0.0 && pDotF < 0.0 || pDotR <= -0.2 && pDotF >= 0.0 && !objectRight || pDotF >= 0.8 && objectFront || objectFront && objectLeft)
	//		return 1;
	//	/*Right forward and no island on rigth*/		/*Right back and no island on right*/
	//	else if (pDotR >= 0.0 && pDotF <= 0.0 || pDotR >= 0.2 && pDotF >= 0.0 && !objectLeft || objectFront && objectRight)
	//		return -1;
	//	/*Cone forward and no island forward*/
	//	else
	//		return 0;
	//	break;
	//}
	//case Behavior::Firing:
	//{
	//	math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - pos;
	//	playerDir.Normalize();
	//	float pDotR = playerDir.Dot(norRight);
	//	float pDotF = playerDir.Dot(norFor);

	//	if (((pDotR >= 0.98 || pDotR <= -0.98) && !objectFront) || objectLeft && objectRight && !objectFront)
	//		return 0;
	//	else if (((pDotR <= 0.98 && pDotF > 0.0 || pDotR < 0.0 && pDotF >= -0.98) && (!objectRight || objectFront || objectLeft && objectFront)) || objectLeft && objectFront)
	//		return 1;
	//	else if (((pDotR <= 0.98 && pDotF > -1.0 || pDotR < 0.0 && pDotF >= 0.98) && (!objectLeft || objectFront && objectRight)) || objectFront && objectRight)
	//		return -1;
	//	else
	//		return 0;

	//	break;
	//}
	//case Behavior::Idle:
	//{
	//	if (!objectFront || objectLeft && objectRight && !objectFront)
	//		return 0;
	//	else if (objectLeft && objectFront || objectFront)
	//		return 1;
	//	else if (objectRight && objectFront)
	//		return -1;
	//	else
	//		return 0;
	//	break;
	//}
	//case Behavior::Searching:
	//{
	//	math::Vector3 playerDir = m_playerShip->m_transform->GetPosition() - m_lastKnownPos;
	//	playerDir.Normalize();
	//	float pDotR = playerDir.Dot(norRight);
	//	float pDotF = playerDir.Dot(norFor);

	//	if (pDotF >= 0.8 && pDotR >= -0.2 && pDotR <= 0.2 && !objectFront)	//Continue forward
	//		return 0;
	//	/*Left forward and no island on left*/			/*Left back and no island on left*/
	//	else if (pDotR < 0.0 && pDotF < 0.0 || pDotR <= -0.2 && pDotF >= 0.0 && !objectRight || pDotF >= 0.8 && objectFront || objectFront && objectLeft)
	//		return 1;
	//	/*Right forward and no island on rigth*/		/*Right back and no island on right*/
	//	else if (pDotR >= 0.0 && pDotF <= 0.0 || pDotR >= 0.2 && pDotF >= 0.0 && !objectLeft || objectFront && objectRight)
	//		return -1;
	//	/*Cone forward and no island forward*/
	//	else
	//		return 0;
	//	break;
	//}
	//default:
	//	break;
	//}
	//
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
		dir = -m_playerShip->m_transform->Forward();		//Should maby be (-m_playerShip->m_transform->Forward())
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
		m_state = Behavior::Idle;
		m_stateStr = "Idle";
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
