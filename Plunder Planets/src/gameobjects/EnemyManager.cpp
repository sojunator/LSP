#include "EnemyManager.h"
#include "BasicEnemy.h"
#include "Toby.h"
#include "ShipStats.h"
void EnemyManager::Start()
{
}

void EnemyManager::Update()
{
	m_delayBetweenSpawnsTimeLeft -= ThomasTime::GetDeltaTime();
	if (m_delayBetweenSpawnsTimeLeft <= 0)
	{
		m_delayBetweenSpawnsTimeLeft = m_delayBetweenSpawns;
	}
}

void EnemyManager::SpawnEnemy(EnemyTypes type, math::Vector3 position, float difficulty)
{
	if (m_amountOfSpecificEnemy[type] >= m_maxAmountOfSpecificEnemy[type]) //too many of that enemy
		return;

	ShipStats shipStats;

	m_amountOfSpecificEnemy[type]++;
	switch (type)
	{
	case EnemyManager::EnemyTypes::BASIC:
		BasicEnemy* enemy = Instantiate<BasicEnemy>(position, math::Quaternion::Identity, m_scene);
		enemy->Init(difficulty);
		break;
	case EnemyManager::EnemyTypes::TOBY:
		Toby* enemy = Instantiate<Toby>(position, math::Quaternion::Identity, m_scene);
		enemy->Init(difficulty);
		break;
	default:
		break;
	}
}

void EnemyManager::RemoveEnemy(EnemyTypes type)
{
}
