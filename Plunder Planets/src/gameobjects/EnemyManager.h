#pragma once
#include "Thomas.h"


using namespace thomas;
using namespace object;


class EnemyManager : public GameObject
{

private:
	enum class EnemyTypes
	{
		BASIC,
		TOBY
	};

public:
	EnemyManager() : GameObject("EnemyManager")
	{

	}

	void Start();
	void Update();
	void SpawnEnemy(EnemyTypes type, math::Vector3 position, float difficulty);

	void RemoveEnemy(EnemyTypes type);

private:
	std::map<EnemyTypes, int> m_maxAmountOfSpecificEnemy;
	std::map<EnemyTypes, int> m_amountOfSpecificEnemy;
	float m_delayBetweenSpawns;
	float m_delayBetweenSpawnsTimeLeft;
	float m_diffculity;
};