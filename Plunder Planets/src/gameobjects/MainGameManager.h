#pragma once
#include "Thomas.h"
#include "EnemyManager.h"

using namespace thomas;
using namespace object;

class MainGameManager : public GameObject
{

public:

public:
	MainGameManager() : GameObject("MainGameManager")
	{

	}

	void Start();
	void Update();

private:
	component::SpriteComponent* m_goldbar;
	component::SpriteComponent* m_goldbarEmpty;
	component::SpriteComponent* m_safeToLeave;
	bool m_wormholeSpawned;
	EnemyManager* m_enemyManager;
	float m_difficulty;
};