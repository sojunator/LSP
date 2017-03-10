#include "AI.h"
#include "../scenes/GameScene.h"
AI::AI() : component::Component("AI")
{
	
}

void AI::Start()
{
	m_currentState = State::Searching;
	m_searchRadius = 800;
	m_fireRadius = 300;
	m_moveToPos = math::Vector3(0,0,0);
}

void AI::OnEnable()
{
	m_target = GameObject::Find("Ship");
}

void AI::Update()
{

	switch (m_currentState)
	{
	case AI::State::Searching:
		SearchingUpdate();
		break;
	case AI::State::Chasing:
		ChasingUpdate();
		break;
	case AI::State::Attacking:
		AttackingUpdate();
		break;
	default:
		break;
	}
}

void AI::ChasingUpdate()
{
	math::Vector3 targetD = m_target->m_transform->GetPosition() - m_gameObject->m_transform->GetPosition();
	float distanceToTarget = targetD.Length();
	targetD.Normalize();

	if (LineOfSight(targetD, distanceToTarget + 1))
	{
		if (distanceToTarget > m_fireRadius)
		{
			m_moveToPos = m_target->m_transform->GetPosition() - targetD*(m_fireRadius-5);
		}
		else
		{
			m_currentState = State::Attacking;
		}
	}
	else
	{
		m_currentState = State::Searching;
	}
}

void AI::SearchingUpdate()
{


	math::Vector3 targetD = m_target->m_transform->GetPosition() - m_gameObject->m_transform->GetPosition();
	float distanceToTarget = targetD.Length();
	targetD.Normalize();

	
	if (distanceToTarget < m_searchRadius && LineOfSight(targetD, distanceToTarget + 1))
	{
		
		m_currentState = State::Chasing;
		m_moveToPos = m_target->m_transform->GetPosition();
	}
	else if(math::Vector3::Distance(m_gameObject->m_transform->GetPosition(), m_moveToPos) <= 2.0)
	{
		float r = ((double)rand() / (RAND_MAX));
		float rads = r * math::PI * 2;
		math::Vector3 randDir = math::Vector3(cosf(rads), 0, sinf(rads));
		randDir.Normalize();

		float r2 = ((double)rand() / (RAND_MAX));
		float randLength = r2 * 50 + 50;

		math::Vector3 newPos = m_gameObject->m_transform->GetPosition() + randDir * randLength;
		while (!LineOfSight(randDir, randLength))
		{
			newPos = m_gameObject->m_transform->GetPosition() + randDir * randLength;
		}
		
		m_moveToPos = newPos;
	}

	
}

void AI::AttackingUpdate()
{
	math::Vector3 targetD = m_target->m_transform->GetPosition() - m_gameObject->m_transform->GetPosition();
	float distanceToTarget = targetD.Length();
	targetD.Normalize();
	if (LineOfSight(targetD, distanceToTarget + 1))
	{
		if (distanceToTarget <= m_fireRadius+200)
		{
			m_moveToPos = m_target->m_transform->GetPosition();
		}
		else
		{
			m_currentState = State::Chasing;
		}

	}
	else
	{
		m_currentState = State::Searching;
	}
}

float AI::GetDistanceToTarget()
{
	return math::Vector3::Distance(m_gameObject->m_transform->GetPosition(), m_target->m_transform->GetPosition());
}

math::Vector3 AI::GetTargetVector()
{
	math::Vector3 targetD = m_gameObject->m_transform->GetPosition() - m_target->m_transform->GetPosition();
	targetD.Normalize();
	return targetD;
}


bool AI::LineOfSight(math::Vector3 dir, float maxLength)
{
	for (float l = 0; l < maxLength; l++)
	{
		math::Vector3 colPos = m_gameObject->m_transform->GetPosition() + dir*l;
		if (GameScene::s_islandManager->Collision(colPos))
			return false;
	}
	return true;
}

AI::State AI::GetState()
{
	return m_currentState;
}



math::Vector3 AI::GetMovePos()
{
	return m_moveToPos;
}

math::Vector3 AI::GetTargetPos()
{
	return m_target->m_transform->GetPosition();
}

void AI::SetFireRadius(float radius)
{
	m_fireRadius = radius;
}


