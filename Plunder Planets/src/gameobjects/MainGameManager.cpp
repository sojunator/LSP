#include "MainGameManager.h"
#include "../scenes/GameScene.h"
#include "ShipStats.h"
#include "Wormhole.h"
void MainGameManager::Start()
{
	m_enemyManager = (EnemyManager*)Find("EnemyManager");
	m_wormholeSpawned = false;

	
	m_goldbar = AddComponent<component::SpriteComponent>();
	m_goldbar->SetName("Goldbar");
	m_goldbar->SetPositionX(Window::GetWidth() - 350);
	m_goldbar->SetPositionY(Window::GetHeight() - 800);
	m_goldbarEmpty = AddComponent<component::SpriteComponent>();
	m_goldbarEmpty->SetName("GoldbarEmpty");
	m_goldbarEmpty->SetPositionX(Window::GetWidth() - 350);
	m_goldbarEmpty->SetPositionY(Window::GetHeight() - 800);
	m_safeToLeave = AddComponent<component::TextComponent>();

}

void MainGameManager::Update()
{
	float difficulty = ShipStats::s_currentLevel + GameScene::s_islandManager->GetLootedTreasure() / 2000.0f;
	m_enemyManager->SetDifficulty(difficulty);

	float maxGold = 2160;
	float scale = GameScene::s_islandManager->GetLootedTreasure() / maxGold;
	m_goldbar->SetScale(math::Vector2(1, scale));
	m_goldbar->SetPositionY(Window::GetHeight() - 800 + (1-scale)*738);


	if (Input::GetKey(Input::Keys::M) && GameScene::s_islandManager->GetLootedTreasure() < maxGold)
		 GameScene::s_islandManager->IncreaseLootedTreasure(50);

	if (GameScene::s_islandManager->GetLootedTreasure() > 1750 && !m_wormholeSpawned)
	{
			Wormhole* wormhole = Instantiate<Wormhole>(math::Vector3(0, 3.0f, 0), math::Quaternion::Identity, m_scene);
			wormhole->SetEndLevel(true);
			m_wormholeSpawned = true;
			m_safeToLeave->SetFont("Pirate");
			m_safeToLeave->SetOutput("Wormhole open\nEnter it to leave planet");
			m_safeToLeave->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_safeToLeave->SetRotation(0.0f);
			m_safeToLeave->SetScale(1.0f);
			m_safeToLeave->SetPositionX(Window::GetWidth() - 720);
			m_safeToLeave->SetPositionY(Window::GetHeight() - 155);
			m_safeToLeave->SetDropshadow(true);
			m_safeToLeave->SetOutline(true);
			m_safeToLeave->SetOrigin(false);
	}
}
