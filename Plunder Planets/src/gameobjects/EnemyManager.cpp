#include "EnemyManager.h"
#include "BasicEnemy.h"
#include "Toby.h"
#include "../scenes/GameScene.h"
void EnemyManager::Start()
{
	m_difficulty = 1;
	m_amountOfSpecificEnemy[EnemyTypes::BASIC] = 0;
	m_amountOfSpecificEnemy[EnemyTypes::TOBY] = 0;
	m_delayBetweenSpawns = 8;
	m_delayBetweenSpawnsTimeLeft = 0;
}

void EnemyManager::Update()
{
	m_maxAmountOfSpecificEnemy[EnemyTypes::BASIC] = m_difficulty * 8;
	m_maxAmountOfSpecificEnemy[EnemyTypes::TOBY] = m_difficulty * 2;
	m_delayBetweenSpawnsTimeLeft -= ThomasTime::GetDeltaTime();
	if (m_delayBetweenSpawnsTimeLeft <= 0)
	{
		float randVal = ((double)rand() / (RAND_MAX));
		int enemyType = (int)(randVal + 0.5);
		LOG(enemyType);
		if (m_amountOfSpecificEnemy[(EnemyTypes)enemyType] >= m_maxAmountOfSpecificEnemy[(EnemyTypes)enemyType])
			enemyType = (enemyType + 1) % 2;
		SpawnEnemy((EnemyTypes)(enemyType), GameScene::s_islandManager->GetRandomPosAroundIsland(50));
		m_delayBetweenSpawnsTimeLeft = m_delayBetweenSpawns - (0.2 * m_difficulty);
	}
}

void EnemyManager::SpawnEnemy(EnemyTypes type, math::Vector3 position)
{
	if (m_amountOfSpecificEnemy[type] >= m_maxAmountOfSpecificEnemy[type]) //too many of that enemy
		return;

	m_amountOfSpecificEnemy[type]++;

	if(type == EnemyManager::EnemyTypes::BASIC)
	{
		BasicEnemy* benemy = Instantiate<BasicEnemy>(position, math::Quaternion::Identity, m_scene);
		benemy->Init(m_difficulty);
	}

	if(type == EnemyManager::EnemyTypes::TOBY)
	{
		Toby* tenemy = Instantiate<Toby>(position, math::Quaternion::Identity, m_scene);
		tenemy->Init(m_difficulty);
	}

}

void EnemyManager::SetDifficulty(float difficulty)
{
	m_difficulty = difficulty;
}

float EnemyManager::GetDifficulity()
{
	return m_difficulty;
}

void EnemyManager::RemoveEnemy(EnemyTypes type)
{
	m_amountOfSpecificEnemy[type]--;
}
