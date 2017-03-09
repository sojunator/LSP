#include "UpgradeMenuObject.h"
#include "../scenes/GameScene.h"
#include "ShipStats.h"
void UpgradeMenuObject::Start()
{
	component::Camera* cam = AddComponent<component::Camera>();
	m_cannonInfo = AddComponent<component::SpriteComponent>();
	m_movementInfo = AddComponent<component::SpriteComponent>();
	m_resourceInfo = AddComponent<component::SpriteComponent>();
	m_shieldInfo = AddComponent<component::SpriteComponent>();
	m_healthInfo = AddComponent<component::SpriteComponent>();
	m_plunderInfo = AddComponent<component::SpriteComponent>();
	m_startButton = AddComponent<component::SpriteComponent>();
	m_cannonIcon = AddComponent<component::SpriteComponent>();
	m_cannonTalent1 = AddComponent<component::SpriteComponent>();
	m_cannonTalent2 = AddComponent<component::SpriteComponent>();
	m_cannonTalent3 = AddComponent<component::SpriteComponent>();
	m_cannonTalent4 = AddComponent<component::SpriteComponent>();
	m_cannonTalent5 = AddComponent<component::SpriteComponent>();
	m_movementIcon = AddComponent<component::SpriteComponent>();
	m_movementTalent1 = AddComponent<component::SpriteComponent>();
	m_movementTalent2 = AddComponent<component::SpriteComponent>();
	m_movementTalent3 = AddComponent<component::SpriteComponent>();
	m_movementTalent4 = AddComponent<component::SpriteComponent>();
	m_movementTalent5 = AddComponent<component::SpriteComponent>();
	m_resourceIcon = AddComponent<component::SpriteComponent>();
	m_resourceTalent1 = AddComponent<component::SpriteComponent>();
	m_resourceTalent2 = AddComponent<component::SpriteComponent>();
	m_resourceTalent3 = AddComponent<component::SpriteComponent>();
	m_resourceTalent4 = AddComponent<component::SpriteComponent>();
	m_resourceTalent5 = AddComponent<component::SpriteComponent>();
	m_shieldIcon = AddComponent<component::SpriteComponent>();
	m_shieldTalent1 = AddComponent<component::SpriteComponent>();
	m_shieldTalent2 = AddComponent<component::SpriteComponent>();
	m_shieldTalent3 = AddComponent<component::SpriteComponent>();
	m_shieldTalent4 = AddComponent<component::SpriteComponent>();
	m_shieldTalent5 = AddComponent<component::SpriteComponent>();
	m_repairIcon = AddComponent<component::SpriteComponent>();
	m_repairTalent1 = AddComponent<component::SpriteComponent>();
	m_plunderIcon = AddComponent<component::SpriteComponent>();
	m_plunderTalent1 = AddComponent<component::SpriteComponent>();
	m_plunderTalent2 = AddComponent<component::SpriteComponent>();
	m_plunderTalent3 = AddComponent<component::SpriteComponent>();
	m_plunderTalent4 = AddComponent<component::SpriteComponent>();
	m_plunderTalent5 = AddComponent<component::SpriteComponent>(); 
	m_exitButton = AddComponent<component::SpriteComponent>();
	m_music = AddComponent<component::SoundComponent>();
	m_wormhole = AddComponent<component::ParticleEmitterComponent>();
	m_currentGold = AddComponent<component::TextComponent>();
	m_currentHealth = AddComponent<component::TextComponent>();
	m_cannonCosts = AddComponent<component::TextComponent>();
	m_movementCosts = AddComponent<component::TextComponent>();
	m_resourceCosts = AddComponent<component::TextComponent>();
	m_shieldCosts = AddComponent<component::TextComponent>();
	m_repairCosts = AddComponent<component::TextComponent>();
	m_plunderSpeedCosts = AddComponent<component::TextComponent>();

	cam->SetFov(50); //makes wormhole fit screen

	m_music->SetClip("mMenuTheme");
	m_music->SetLooping(true);
	m_music->Play();

	int currentGoldCast = ShipStats::s_playerStats->GetTreasure();
	m_currentGold->SetFont("Pirate");
	m_currentGold->SetOutput("Current gold: " + std::to_string(currentGoldCast));
	m_currentGold->SetColor(math::Vector3(1.0f, 0.85f, 0.0f));
	m_currentGold->SetRotation(0.0f);
	m_currentGold->SetScale(2.0f);
	m_currentGold->SetPositionX(35);
	m_currentGold->SetPositionY(15);
	m_currentGold->SetDropshadow(true);
	m_currentGold->SetOutline(true);
	m_currentGold->SetOrigin(false);

	int currentHealthCast = ShipStats::s_playerStats->GetHealthAmount() * 100;
	m_currentHealth->SetFont("Pirate");
	m_currentHealth->SetOutput("Current health: " + std::to_string(currentHealthCast) + "/ 100");
	m_currentHealth->SetColor(math::Vector3(1.0f, 0.85f, 0.0f));
	m_currentHealth->SetRotation(0.0f);
	m_currentHealth->SetScale(1.0f);
	m_currentHealth->SetPositionX(1250);
	m_currentHealth->SetPositionY(45);
	m_currentHealth->SetDropshadow(true);
	m_currentHealth->SetOutline(true);
	m_currentHealth->SetOrigin(false);

	m_cannonInfo->SetName("CannonInfo");
	m_cannonInfo->SetPositionX(680);
	m_cannonInfo->SetPositionY(150);
	m_cannonInfo->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonInfo->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonInfo->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonInfo->SetInteractable(false);

	m_movementInfo->SetName("MovementInfo");
	m_movementInfo->SetPositionX(680);
	m_movementInfo->SetPositionY(150);
	m_movementInfo->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementInfo->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementInfo->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementInfo->SetInteractable(false);

	m_resourceInfo->SetName("ResourceInfo");
	m_resourceInfo->SetPositionX(680);
	m_resourceInfo->SetPositionY(150);
	m_resourceInfo->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceInfo->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceInfo->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceInfo->SetInteractable(false);

	m_shieldInfo->SetName("ShieldInfo");
	m_shieldInfo->SetPositionX(680);
	m_shieldInfo->SetPositionY(150);
	m_shieldInfo->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldInfo->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldInfo->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldInfo->SetInteractable(false);

	m_healthInfo->SetName("HealthInfo");
	m_healthInfo->SetPositionX(680);
	m_healthInfo->SetPositionY(150);
	m_healthInfo->SetScale(math::Vector2(1.0f, 1.0f));
	m_healthInfo->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_healthInfo->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_healthInfo->SetInteractable(false);

	m_plunderInfo->SetName("PlunderInfo");
	m_plunderInfo->SetPositionX(680);
	m_plunderInfo->SetPositionY(150);
	m_plunderInfo->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderInfo->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderInfo->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderInfo->SetInteractable(false);

	m_startButton->SetName("UpgradeMenuStart");
	m_startButton->SetPositionX(1450);
	m_startButton->SetPositionY(970);
	m_startButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_startButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_startButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_startButton->SetInteractable(true);


	//Create Cannon sprites
	m_cannonIcon->SetName("CannonIcon");
	m_cannonIcon->SetPositionX(50);
	m_cannonIcon->SetPositionY(200);
	m_cannonIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonIcon->SetInteractable(true);

	m_cannonTalent1->SetName("Talent");
	m_cannonTalent1->SetPositionX(220);
	m_cannonTalent1->SetPositionY(250);
	m_cannonTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent1->SetInteractable(false);

	m_cannonTalent2->SetName("Talent");
	m_cannonTalent2->SetPositionX(285);
	m_cannonTalent2->SetPositionY(250);
	m_cannonTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent2->SetInteractable(false);

	m_cannonTalent3->SetName("Talent");
	m_cannonTalent3->SetPositionX(350);
	m_cannonTalent3->SetPositionY(250);
	m_cannonTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent3->SetInteractable(false);

	m_cannonTalent4->SetName("Talent");
	m_cannonTalent4->SetPositionX(415);
	m_cannonTalent4->SetPositionY(250);
	m_cannonTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent4->SetInteractable(false);

	m_cannonTalent5->SetName("Talent");
	m_cannonTalent5->SetPositionX(480);
	m_cannonTalent5->SetPositionY(225);
	m_cannonTalent5->SetScale(math::Vector2(2.0f, 2.0f));
	m_cannonTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent5->SetInteractable(false);

	//Create Movement sprites
	m_movementIcon->SetName("MovementIcon");
	m_movementIcon->SetPositionX(50);
	m_movementIcon->SetPositionY(425);
	m_movementIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementIcon->SetInteractable(true);

	m_movementTalent1->SetName("Talent");
	m_movementTalent1->SetPositionX(220);
	m_movementTalent1->SetPositionY(475);
	m_movementTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent1->SetInteractable(false);

	m_movementTalent2->SetName("Talent");
	m_movementTalent2->SetPositionX(285);
	m_movementTalent2->SetPositionY(475);
	m_movementTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent2->SetInteractable(false);

	m_movementTalent3->SetName("Talent");
	m_movementTalent3->SetPositionX(350);
	m_movementTalent3->SetPositionY(475);
	m_movementTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent3->SetInteractable(false);

	m_movementTalent4->SetName("Talent");
	m_movementTalent4->SetPositionX(415);
	m_movementTalent4->SetPositionY(475);
	m_movementTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent4->SetInteractable(false);

	m_movementTalent5->SetName("Talent");
	m_movementTalent5->SetPositionX(480);
	m_movementTalent5->SetPositionY(450);
	m_movementTalent5->SetScale(math::Vector2(2.0f, 2.0f));
	m_movementTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent5->SetInteractable(false);

	//Create Resource sprites
	m_resourceIcon->SetName("ResourceIcon");
	m_resourceIcon->SetPositionX(50);
	m_resourceIcon->SetPositionY(650);
	m_resourceIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceIcon->SetInteractable(true);

	m_resourceTalent1->SetName("Talent");
	m_resourceTalent1->SetPositionX(220);
	m_resourceTalent1->SetPositionY(700);
	m_resourceTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent1->SetInteractable(false);

	m_resourceTalent2->SetName("Talent");
	m_resourceTalent2->SetPositionX(285);
	m_resourceTalent2->SetPositionY(700);
	m_resourceTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent2->SetInteractable(false);

	m_resourceTalent3->SetName("Talent");
	m_resourceTalent3->SetPositionX(350);
	m_resourceTalent3->SetPositionY(700);
	m_resourceTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent3->SetInteractable(false);

	m_resourceTalent4->SetName("Talent");
	m_resourceTalent4->SetPositionX(415);
	m_resourceTalent4->SetPositionY(700);
	m_resourceTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent4->SetInteractable(false);

	m_resourceTalent5->SetName("Talent");
	m_resourceTalent5->SetPositionX(480);
	m_resourceTalent5->SetPositionY(675);
	m_resourceTalent5->SetScale(math::Vector2(2.0f, 2.0f));
	m_resourceTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent5->SetInteractable(false);

	//Create Shield sprites
	m_shieldIcon->SetName("ShieldIcon");
	m_shieldIcon->SetPositionX(1720);
	m_shieldIcon->SetPositionY(200);
	m_shieldIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldIcon->SetInteractable(true);

	m_shieldTalent1->SetName("Talent");
	m_shieldTalent1->SetPositionX(1600);
	m_shieldTalent1->SetPositionY(225);
	m_shieldTalent1->SetScale(math::Vector2(2.0f, 2.0f));
	m_shieldTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent1->SetInteractable(false);

	m_shieldTalent2->SetName("Talent");
	m_shieldTalent2->SetPositionX(1535);
	m_shieldTalent2->SetPositionY(250);
	m_shieldTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent2->SetInteractable(false);

	m_shieldTalent3->SetName("Talent");
	m_shieldTalent3->SetPositionX(1470);
	m_shieldTalent3->SetPositionY(250);
	m_shieldTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent3->SetInteractable(false);

	m_shieldTalent4->SetName("Talent");
	m_shieldTalent4->SetPositionX(1405);
	m_shieldTalent4->SetPositionY(250);
	m_shieldTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent4->SetInteractable(false);

	m_shieldTalent5->SetName("Talent");
	m_shieldTalent5->SetPositionX(1340);
	m_shieldTalent5->SetPositionY(250);
	m_shieldTalent5->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent5->SetInteractable(false);

	//Create Repair sprites
	m_repairIcon->SetName("RepairIcon");
	m_repairIcon->SetPositionX(1720);
	m_repairIcon->SetPositionY(425);
	m_repairIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_repairIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_repairIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_repairIcon->SetInteractable(true);

	m_repairTalent1->SetName("Talent");
	m_repairTalent1->SetPositionX(1600);
	m_repairTalent1->SetPositionY(450);
	m_repairTalent1->SetScale(math::Vector2(2.0f, 2.0f));
	m_repairTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_repairTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_repairTalent1->SetInteractable(false);

	//Create Plunder sprites
	m_plunderIcon->SetName("PlunderIcon");
	m_plunderIcon->SetPositionX(1720);
	m_plunderIcon->SetPositionY(650);
	m_plunderIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderIcon->SetInteractable(true);

	m_plunderTalent1->SetName("Talent");
	m_plunderTalent1->SetPositionX(1650);
	m_plunderTalent1->SetPositionY(700);
	m_plunderTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent1->SetInteractable(false);

	m_plunderTalent2->SetName("Talent");
	m_plunderTalent2->SetPositionX(1585);
	m_plunderTalent2->SetPositionY(700);
	m_plunderTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent2->SetInteractable(false);

	m_plunderTalent3->SetName("Talent");
	m_plunderTalent3->SetPositionX(1520);
	m_plunderTalent3->SetPositionY(700);
	m_plunderTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent3->SetInteractable(false);

	m_plunderTalent4->SetName("Talent");
	m_plunderTalent4->SetPositionX(1455);
	m_plunderTalent4->SetPositionY(700);
	m_plunderTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent4->SetInteractable(false);

	m_plunderTalent5->SetName("Talent");
	m_plunderTalent5->SetPositionX(1340);
	m_plunderTalent5->SetPositionY(675);
	m_plunderTalent5->SetScale(math::Vector2(2.0f, 2.0f));
	m_plunderTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent5->SetInteractable(false);


	m_exitButton->SetName("UpgradeMenuExit");
	m_exitButton->SetPositionX(50);
	m_exitButton->SetPositionY(970);
	m_exitButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_exitButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_exitButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_exitButton->SetInteractable(true);


	m_wormhole->SetTexture("../res/textures/wormhole.png");
	m_wormhole->SetLooping(true);
	m_wormhole->SetSpeed(0);
	m_wormhole->SetLifeTime(72.0);
	m_wormhole->SetEmissionRate(1.0f / 72.0);
	m_wormhole->SetSize(65);
	m_wormhole->SetRotationSpeed(math::DegreesToRadians(5));
	m_wormhole->SetOffset(cam->m_gameObject->m_transform->Forward() * 50);
	m_wormhole->StartEmitting();

}

void UpgradeMenuObject::Update()
{
	m_delay = m_delay - ThomasTime::GetDeltaTime();
	m_upgradeDelay = m_upgradeDelay - ThomasTime::GetDeltaTime(); //Upgrade delay so can't spam and glitch out upgrades.

	UpdateGoldCounter();
	UpdateHealthCounter();

	SetSelectedObject();
	
	if ((Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space) || Input::GetButtonDown(Input::Buttons::B) || Input::GetKeyDown(Input::Keys::Back)) && m_upgradeDelay < 0.1f)
	{
		bool upgrade = false;
		bool undo = false;
		if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space)) //We decided to upgrade
			upgrade = true;
		if (Input::GetButtonDown(Input::Buttons::B) || Input::GetKeyDown(Input::Keys::Back)) //We decided to undo our upgrade
			undo = true;

		CannonCheck(upgrade, undo);

		MovementCheck(upgrade, undo);
		
		ResourceCheck(upgrade, undo);

		ShieldCheck(upgrade, undo);

		RepairCheck(upgrade, undo);

		PlunderCheck(upgrade, undo);

		m_upgradeDelay = 0.3f; //Reset upgrade delay
	}

	Navigation();
	
	if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK))
		Scene::LoadScene<MenuScene>();

	if (Input::GetKeyDown(Input::Keys::Enter) || Input::GetButtonDown(Input::Buttons::START))
	{
		Scene::LoadScene<GameScene>();		
	}
}

void UpgradeMenuObject::UpdateGoldCounter()
{
	int currentGoldCast = ShipStats::s_playerStats->GetTreasure();
	m_currentGold->SetOutput("Current gold: " + std::to_string(currentGoldCast));
}

void UpgradeMenuObject::UpdateHealthCounter()
{
	int currentHealthCast = ShipStats::s_playerStats->GetHealthAmount() * 100;
	m_currentHealth->SetOutput("Current health: " + std::to_string(currentHealthCast) + "/ 100");
}

void UpgradeMenuObject::CannonCheck(bool upgrade, bool undo)
{
	if (m_cannonIcon->isHovering())
	{
		if ((upgrade && !m_cannonCheck[0]) || (undo && !m_cannonCheck[1] && m_cannonCheck[0])) //First time choosing to upgrade Cannon
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 200))
			{
				m_cannonTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[0] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(1); //Increase Cannon Dmg/Spread/Quantity first time
				ShipStats::s_playerStats->SetTreasure(-200);
				m_cannonIcon->SetName("CannonIcon1");
			}
			else if (undo) //Doesn't need an if(undo), could just be else, but more clear what is happening this way
			{
				m_cannonTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[0] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(0); //Undo first upgrade
				ShipStats::s_playerStats->SetTreasure(200);
				m_cannonIcon->SetName("CannonIcon");

			}
		}
		else if ((upgrade && m_cannonCheck[0] && !m_cannonCheck[1]) || (undo && !m_cannonCheck[2] && m_cannonCheck[1]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 300))
			{
				m_cannonTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[1] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(2);//Increase Cannon Dmg/Spread/Quantity second time
				ShipStats::s_playerStats->SetTreasure(-300);
				m_cannonIcon->SetName("CannonIcon2");
			}
			else if (undo)
			{
				m_cannonTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[1] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(1);//Undo second upgrade
				ShipStats::s_playerStats->SetTreasure(300);
				m_cannonIcon->SetName("CannonIcon1");
			}
		}
		else if ((upgrade && m_cannonCheck[1] && !m_cannonCheck[2]) || (undo && !m_cannonCheck[3] && m_cannonCheck[2]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 500))
			{
				m_cannonTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[2] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(3);//Increase Cannon Dmg/Spread/Quantity third time
				ShipStats::s_playerStats->SetTreasure(-500);
				m_cannonIcon->SetName("CannonIcon3");
			}
			else if (undo)
			{
				m_cannonTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[2] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(2);//Undo third upgrade
				ShipStats::s_playerStats->SetTreasure(500);
				m_cannonIcon->SetName("CannonIcon2");
			}
		}
		else if ((upgrade && m_cannonCheck[2] && !m_cannonCheck[3]) || (undo && !m_cannonCheck[4] && m_cannonCheck[3]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 750))
			{
				m_cannonTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[3] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(4);//Increase Cannon Dmg/Spread/Quantity fourth time
				ShipStats::s_playerStats->SetTreasure(-750);
				m_cannonIcon->SetName("CannonIcon4");
			}
			else if (undo)
			{
				m_cannonTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[3] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(3);//Undo fourth upgrade
				ShipStats::s_playerStats->SetTreasure(750);
				m_cannonIcon->SetName("CannonIcon3");
			}
		}
		else if ((upgrade && m_cannonCheck[3] && !m_cannonCheck[4]) || (undo && m_cannonCheck[4]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 1000))
			{
				m_cannonTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[4] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(5);//Increase Cannon Dmg/Spread/Quantity fifth time
				ShipStats::s_playerStats->SetTreasure(-1000);
				m_cannonIcon->SetName("CannonIcon5");
				//Shoot double projectiles
			}
			else if (undo)
			{
				m_cannonTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[4] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(4);//Undo fifth upgrade
				ShipStats::s_playerStats->SetTreasure(1000);
				m_cannonIcon->SetName("CannonIcon4");
			}
		}
	}
}

void UpgradeMenuObject::MovementCheck(bool upgrade, bool undo)
{
	if (m_movementIcon->isHovering())
	{
		if ((upgrade && !m_movementCheck[0]) || (undo && !m_movementCheck[1] && m_movementCheck[0])) //First time choosing to upgrade Movement
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 200))
			{
				m_movementTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[0] = true;
				ShipStats::s_playerStats->IncreaseSpeed(1);//Increase movement speed first time
				ShipStats::s_playerStats->SetTreasure(-200);
				m_movementIcon->SetName("MovementIcon1");
			}
			if (undo)
			{
				m_movementTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[0] = false;
				ShipStats::s_playerStats->IncreaseSpeed(0);//Undo first movement upgrade
				ShipStats::s_playerStats->SetTreasure(200);
				m_movementIcon->SetName("MovementIcon");
			}
		}
		else if ((upgrade && m_movementCheck[0] && !m_movementCheck[1]) || (undo && !m_movementCheck[2] && m_movementCheck[1]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 300))
			{
				m_movementTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[1] = true;
				ShipStats::s_playerStats->IncreaseSpeed(2);//Increase movement speed second time
				ShipStats::s_playerStats->SetTreasure(-300);
				m_movementIcon->SetName("MovementIcon2");
			}
			if (undo)
			{
				m_movementTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[1] = false;
				ShipStats::s_playerStats->IncreaseSpeed(1);//Undo second movement upgrade
				ShipStats::s_playerStats->SetTreasure(300);
				m_movementIcon->SetName("MovementIcon1");
			}
		}
		else if ((upgrade && m_movementCheck[1] && !m_movementCheck[2]) || (undo && !m_movementCheck[3] && m_movementCheck[2]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 500))
			{
				m_movementTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[2] = true;
				ShipStats::s_playerStats->IncreaseSpeed(3);//Increase movement speed third time
				ShipStats::s_playerStats->SetTreasure(-500);
				m_movementIcon->SetName("MovementIcon3");
			}
			if (undo)
			{
				m_movementTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[2] = false;
				ShipStats::s_playerStats->IncreaseSpeed(2);//Undo third movement upgrade
				ShipStats::s_playerStats->SetTreasure(500);
				m_movementIcon->SetName("MovementIcon2");
			}
		}
		else if ((upgrade && m_movementCheck[2] && !m_movementCheck[3]) || (undo && !m_movementCheck[4] && m_movementCheck[3]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 750))
			{
				m_movementTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[3] = true;
				ShipStats::s_playerStats->IncreaseSpeed(4);//Increase movement speed fourth time
				ShipStats::s_playerStats->SetTreasure(-750);
				m_movementIcon->SetName("MovementIcon4");
			}
			if (undo)
			{
				m_movementTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[3] = false;
				ShipStats::s_playerStats->IncreaseSpeed(3);//Undo fourth movement upgrade
				ShipStats::s_playerStats->SetTreasure(750);
				m_movementIcon->SetName("MovementIcon3");
			}
		}
		else if ((upgrade && m_movementCheck[3] && !m_movementCheck[4]) || (undo && m_movementCheck[4] && m_movementCheck[4]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 1000))
			{
				m_movementTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[4] = true;
				ShipStats::s_playerStats->IncreaseSpeed(5);//Increase movement speed fifth time
				ShipStats::s_playerStats->SetTreasure(-1000);
				m_movementIcon->SetName("MovementIcon5");
			}
			if (undo)
			{
				m_movementTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[4] = false;
				ShipStats::s_playerStats->IncreaseSpeed(4);//Undo fifth movement upgrade
				ShipStats::s_playerStats->SetTreasure(1000);
				m_movementIcon->SetName("MovementIcon4");
			}
		}
	}
}

void UpgradeMenuObject::ResourceCheck(bool upgrade, bool undo)
{
	if (m_resourceIcon->isHovering())
	{
		if ((upgrade && !m_resourceCheck[0]) || (undo && !m_resourceCheck[1] && m_resourceCheck[0])) //First time choosing to upgrade Resource Cost Reduction
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 200))
			{
				m_resourceTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[0] = true;
				ShipStats::s_playerStats->DecreaseCosts(1);//Decrease resource costs first time
				ShipStats::s_playerStats->SetTreasure(-200);
			}
			else if (undo)
			{
				m_resourceTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[0] = false;
				ShipStats::s_playerStats->DecreaseCosts(0);//Undo first resource cost reduction
				ShipStats::s_playerStats->SetTreasure(200);
			}
		}
		else if ((upgrade && m_resourceCheck[0] && !m_resourceCheck[1]) || (undo && !m_resourceCheck[2] && m_resourceCheck[1]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 300))
			{
				m_resourceTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[1] = true;
				ShipStats::s_playerStats->DecreaseCosts(2);//Decrease resource costs second time
				ShipStats::s_playerStats->SetTreasure(-300);
			}
			else if (undo)
			{
				m_resourceTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[1] = false;
				ShipStats::s_playerStats->DecreaseCosts(1);//Undo second resource cost reduction
				ShipStats::s_playerStats->SetTreasure(300);
			}
		}
		else if ((upgrade && m_resourceCheck[1] && !m_resourceCheck[2]) || (undo && !m_resourceCheck[3] && m_resourceCheck[2]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 500))
			{
				m_resourceTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[2] = true;
				ShipStats::s_playerStats->DecreaseCosts(3);//Decrease resource costs third time
				ShipStats::s_playerStats->SetTreasure(-500);
			}
			else if (undo)
			{
				m_resourceTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[2] = false;
				ShipStats::s_playerStats->DecreaseCosts(2);//Undo third resource cost reduction
				ShipStats::s_playerStats->SetTreasure(500);
			}
		}
		else if ((upgrade && m_resourceCheck[2] && !m_resourceCheck[3]) || (undo && !m_resourceCheck[4] && m_resourceCheck[3]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 750))
			{
				m_resourceTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[3] = true;
				ShipStats::s_playerStats->DecreaseCosts(4);//Decrease resource costs fourth time
				ShipStats::s_playerStats->SetTreasure(-750);
			}
			else if (undo)
			{
				m_resourceTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[3] = false;
				ShipStats::s_playerStats->DecreaseCosts(3);//Undo fourth resource cost reduction
				ShipStats::s_playerStats->SetTreasure(750);
			}
		}
		else if ((upgrade && m_resourceCheck[3] && !m_resourceCheck[4]) || (undo && m_resourceCheck[4]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 1000))
			{
				m_resourceTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[4] = true;
				ShipStats::s_playerStats->DecreaseCosts(5);//Decrease resource costs fifth time
				ShipStats::s_playerStats->SetTreasure(-1000);
			}
			else if (undo)
			{
				m_resourceTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[4] = false;
				ShipStats::s_playerStats->DecreaseCosts(4);//Undo fifth resource cost reduction
				ShipStats::s_playerStats->SetTreasure(1000);
			}
		}
	}
}

void UpgradeMenuObject::ShieldCheck(bool upgrade, bool undo)
{
	if (m_shieldIcon->isHovering())
	{
		if ((upgrade && !m_shieldCheck[0]) || (undo && !m_shieldCheck[1] && m_shieldCheck[0])) //First time choosing to upgrade Shield
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 750))
			{
				m_shieldTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[0] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(1);//Buy Shield
				ShipStats::s_playerStats->SetTreasure(-750);
				m_shieldIcon->SetName("ShieldIcon1");
			}
			else if (undo)
			{
				m_shieldTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[0] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(0);//Undo last shield upgrade
				ShipStats::s_playerStats->SetTreasure(750);
				m_shieldIcon->SetName("ShieldIcon");
			}
		}
		else if ((upgrade && m_shieldCheck[0] && !m_shieldCheck[1]) || (undo && !m_shieldCheck[2] && m_shieldCheck[1]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 250))
			{
				m_shieldTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[1] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(2);//Buy Shield
				ShipStats::s_playerStats->SetTreasure(-250);
				m_shieldIcon->SetName("ShieldIcon2");
			}
			else if (undo)
			{
				m_shieldTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[1] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(1);//Undo last shield upgrade
				ShipStats::s_playerStats->SetTreasure(250);
				m_shieldIcon->SetName("ShieldIcon1");
			}
		}
		else if ((upgrade && m_shieldCheck[1] && !m_shieldCheck[2]) || (undo && !m_shieldCheck[3] && m_shieldCheck[2]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 250))
			{
				m_shieldTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[2] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(3);//Buy Shield
				ShipStats::s_playerStats->SetTreasure(-250);
				m_shieldIcon->SetName("ShieldIcon3");
			}
			else if (undo)
			{
				m_shieldTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[2] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(2);//Undo last shield upgrade
				ShipStats::s_playerStats->SetTreasure(250);
				m_shieldIcon->SetName("ShieldIcon2");
			}
		}
		else if ((upgrade && m_shieldCheck[2] && !m_shieldCheck[3]) || (undo && !m_shieldCheck[4] && m_shieldCheck[3]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 250))
			{
				m_shieldTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[3] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(4);//Buy Shield
				ShipStats::s_playerStats->SetTreasure(-250);
				m_shieldIcon->SetName("ShieldIcon4");
			}
			else if (undo)
			{
				m_shieldTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[3] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(3);//Undo last shield upgrade
				ShipStats::s_playerStats->SetTreasure(250);
				m_shieldIcon->SetName("ShieldIcon3");
			}
		}
		else if ((upgrade && m_shieldCheck[3] && !m_shieldCheck[4]) || (undo && m_shieldCheck[4]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 250))
			{
				m_shieldTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[4] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(5);//Buy Shield
				ShipStats::s_playerStats->SetTreasure(-250);
				m_shieldIcon->SetName("ShieldIcon5");
			}
			else if (undo)
			{
				m_shieldTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[4] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(4);//Undo last shield upgrade
				ShipStats::s_playerStats->SetTreasure(250);
				m_shieldIcon->SetName("ShieldIcon4");
			}
		}
	}
}

void UpgradeMenuObject::RepairCheck(bool upgrade, bool undo)
{
	if (m_repairIcon->isHovering())
	{
		if ((!m_repairCheck[0] && upgrade && (ShipStats::s_playerStats->GetHealthAmount() != 1))|| (m_healthRepairCounts > 0 && undo)) //If upgrading or undoing, checks if not already full hp
		{
			float goldCost = 100 * (1 - ShipStats::s_playerStats->GetHealthAmount()) * 15;
			float goldRefund = 100 * (ShipStats::s_playerStats->GetPlaceholderHealthAmount()) * 15;

			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= goldCost))
			{
				if (ShipStats::s_playerStats->GetHealthAmount() <= 0.75)
				{
					m_repairTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
					m_refundHolder = 25;
					m_healthRepairCounts += 1;

					goldCost = 25 * 15; //Can Repair 25 health, costs 15 each
					ShipStats::s_playerStats->RepairHealth(1); //Repair health
					ShipStats::s_playerStats->SetTreasure(-goldCost);
					if(ShipStats::s_playerStats->GetHealthAmount() == 1)
						m_repairCheck[0] = true;
				}
				else if (ShipStats::s_playerStats->GetHealthAmount() > 0.75)
				{
					m_repairTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
					int castHealth = ShipStats::s_playerStats->GetHealthAmount() * 100;
					m_refundHolder = 100 - castHealth;
					m_healthRepairCounts += 1;
					
					goldCost = (100 - castHealth) * 15; //Can Repair less than 25 health, costs 15 each
					ShipStats::s_playerStats->RepairHealth(1); //Repair health
					ShipStats::s_playerStats->SetTreasure(-goldCost);
					if (ShipStats::s_playerStats->GetHealthAmount() == 1)
						m_repairCheck[0] = true;
				}
			}
			else if (undo)
			{
				m_repairTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				if (ShipStats::s_playerStats->GetHealthAmount() == 1)
					goldRefund = m_refundHolder * 15; //Refunds less than 25 health * 15 gold each
				else
					goldRefund = 25 * 15;
				ShipStats::s_playerStats->RepairHealth(0); //Reset health
				ShipStats::s_playerStats->SetTreasure(goldRefund);
				m_healthRepairCounts -= 1;
				m_repairCheck[0] = false;
			}
		}
	}
}

void UpgradeMenuObject::PlunderCheck(bool upgrade, bool undo)
{
	if (m_plunderIcon->isHovering())
	{
		if ((upgrade && !m_plunderCheck[0]) || (!m_plunderCheck[1] && undo && m_plunderCheck[0]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 200))
			{
				m_plunderTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_plunderCheck[0] = true;
				ShipStats::s_playerStats->IncreasePlunderSpeed(1); //Increase plunder speed first time
				ShipStats::s_playerStats->SetTreasure(-200);
			}
			if (undo)
			{
				m_plunderTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_plunderCheck[0] = false;
				ShipStats::s_playerStats->IncreasePlunderSpeed(0); //Increase plunder speed first time
				ShipStats::s_playerStats->SetTreasure(200);
			}
		}
		else if ((upgrade && m_plunderCheck[0] && !m_plunderCheck[1]) || (!m_plunderCheck[2] && undo && m_plunderCheck[1]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 300))
			{
				m_plunderTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_plunderCheck[1] = true;
				ShipStats::s_playerStats->IncreasePlunderSpeed(2); //Increase plunder speed second time
				ShipStats::s_playerStats->SetTreasure(-300);
			}
			if (undo)
			{
				m_plunderTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_plunderCheck[1] = false;
				ShipStats::s_playerStats->IncreasePlunderSpeed(1); //Decrease second plunder speed
				ShipStats::s_playerStats->SetTreasure(300);
			}
		}
		else if ((upgrade && m_plunderCheck[1] && !m_plunderCheck[2]) || (!m_plunderCheck[3] && undo && m_plunderCheck[2]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 500))
			{
				m_plunderTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_plunderCheck[2] = true;
				ShipStats::s_playerStats->IncreasePlunderSpeed(3); //Decrease third plunder speed
				ShipStats::s_playerStats->SetTreasure(-500);
			}
			if (undo)
			{
				m_plunderTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_plunderCheck[2] = false;
				ShipStats::s_playerStats->IncreasePlunderSpeed(2); //Decrease third plunder speed
				ShipStats::s_playerStats->SetTreasure(500);
			}
		}
		else if ((upgrade && m_plunderCheck[2] && !m_plunderCheck[3]) || (!m_plunderCheck[4] && undo && m_plunderCheck[3]))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 750))
			{
				m_plunderTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_plunderCheck[3] = true;
				ShipStats::s_playerStats->IncreasePlunderSpeed(4); //Increase plunder speed fourth time
				ShipStats::s_playerStats->SetTreasure(-750);
			}
			if (undo)
			{
				m_plunderTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_plunderCheck[3] = false;
				ShipStats::s_playerStats->IncreasePlunderSpeed(3); //Decrease fourth plunder speed
				ShipStats::s_playerStats->SetTreasure(750);
			}
		}
		else if ((upgrade && m_plunderCheck[3] && !m_plunderCheck[4]) || (m_plunderCheck[4] && undo))
		{
			if (upgrade && (ShipStats::s_playerStats->GetTreasure() >= 1000))
			{
				m_plunderTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_plunderCheck[4] = true;
				ShipStats::s_playerStats->IncreasePlunderSpeed(5); //Increase plunder speed fifth time
				ShipStats::s_playerStats->SetTreasure(-1000);
			}
			if (undo)
			{
				m_plunderTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_plunderCheck[4] = false;
				ShipStats::s_playerStats->IncreasePlunderSpeed(4); //Decrease fifth plunder speed
				ShipStats::s_playerStats->SetTreasure(1000);
			}
		}
	}
}

void UpgradeMenuObject::Navigation()
{
	//Menu navigation, check if any navigating buttons are pressed before making selection moves
	if ((Input::GetLeftStickY() && m_delay < 0.1f) || (Input::GetButton(Input::Buttons::DPAD_DOWN) && m_delay < 0.1f)
		|| (Input::GetButton(Input::Buttons::DPAD_UP) && m_delay < 0.1f) || (Input::GetKey(Input::Keys::Down) && m_delay < 0.1f)
		|| (Input::GetKey(Input::Keys::Up) && m_delay < 0.1f) || Input::GetButton(Input::Buttons::DPAD_RIGHT) || Input::GetButton(Input::Buttons::DPAD_LEFT)
		|| Input::GetLeftStickX() && m_delay < 0.1f || Input::GetKey(Input::Keys::Right) || Input::GetKey(Input::Keys::Left))
	{
		for (int i = 0; i < 3; i++) //three rows currently
		{
			if ((m_yArray[i] == 1) && ((Input::GetLeftStickY() > abs(Input::GetLeftStickX())) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up))) //Player presses up
			{
				if ((m_xArray[1] == 1) && (m_yArray[0] == 1) && ((Input::GetLeftStickY() > abs(Input::GetLeftStickX())) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up))) //Player presses up, we're right side top, jump to left, continue scrolling
				{
					m_xArray[0] = 1;
					m_xArray[1] = 0;
					m_yArray[0] = 0;
					m_yArray[1] = 0;
					m_yArray[2] = 1;
				}
				if ((m_xArray[0] == 1) && (m_yArray[0] == 1) && ((Input::GetLeftStickY() > abs(Input::GetLeftStickX())) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up))) //Player presses up, we're left side top, jump to right bottom, continue scrolling
				{
					m_xArray[0] = 0;
					m_xArray[1] = 1;
					m_yArray[0] = 0;
					m_yArray[1] = 0;
					m_yArray[2] = 1;
				}
				else //Player wants to go up, we're already left side
				{
					m_yArray[i - 1] = 1;//Select Sprite Above
					m_yArray[i] = 0;	//Deselect Current Sprite
				}
				break;
			}
			else if ((m_yArray[i] == 1) && ((Input::GetLeftStickY() < -abs(Input::GetLeftStickX())) || Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetKey(Input::Keys::Down))) //Player presses down
			{
				if ((m_yArray[2] == 1) && (m_xArray[0] == 1) && ((Input::GetLeftStickY() < -(abs(Input::GetLeftStickX()))) || Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetKey(Input::Keys::Down))) //Player presses down, we're already at the bottom left, jump to right side, continue scrolling there
				{
					m_yArray[0] = 1; //set
					m_yArray[2] = 0; //reset 
					m_xArray[0] = 0; //reset
					m_xArray[1] = 1; //set
					break;
				}
				if ((m_yArray[2] == 1) && (m_xArray[1] == 1) && ((Input::GetLeftStickY() < -(abs(Input::GetLeftStickX()))) || Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetKey(Input::Keys::Down))) //Player presses down, we're already at the bottom left, jump to right side, continue scrolling there
				{
					m_yArray[0] = 1; //set
					m_yArray[2] = 0; //reset 
					m_xArray[0] = 1; //reset
					m_xArray[1] = 0; //set
					break;
				}
				else //Player wants to go down, we're already left side
				{
					m_yArray[i + 1] = 1;
					m_yArray[i] = 0;
				}
				break;
			}
			else if ((m_xArray[0] == 1) && ((Input::GetLeftStickX() > abs(Input::GetLeftStickY())) || Input::GetButton(Input::Buttons::DPAD_RIGHT) || Input::GetKey(Input::Keys::Right))) //Player presses right
			{
				m_xArray[0] = 0;
				m_xArray[1] = 1;
				break;
			}
			else if ((m_xArray[1] == 1) && ((Input::GetLeftStickX() < -abs(Input::GetLeftStickY())) || Input::GetButton(Input::Buttons::DPAD_LEFT) || Input::GetKey(Input::Keys::Left))) //Player presses left
			{
				m_xArray[0] = 1;
				m_xArray[1] = 0;
			}
		}
		m_delay = 0.3f;
	}
}

void UpgradeMenuObject::SetSelectedObject()
{
	for (int i = 0; i < 3; i++) //Move to own function
	{
		if ((m_yArray[i] == 1) && (m_xArray[0] == 1)) //Left side is selected, set highlights
		{
			if (i == 0)
			{
				m_cannonIcon->SetHovering(true);
				m_cannonInfo->SetActive(true);
			}
			if (i == 1)
			{
				m_movementIcon->SetHovering(true);
				m_movementInfo->SetActive(true);
			}
			if (i == 2)
			{
				m_resourceIcon->SetHovering(true);
				m_resourceInfo->SetActive(true);
			}
			m_shieldIcon->SetHovering(false);
			m_shieldInfo->SetActive(false);
			m_repairIcon->SetHovering(false);
			m_healthInfo->SetActive(false);
			m_plunderIcon->SetHovering(false);
			m_plunderInfo->SetActive(false);
		}
		else if ((m_yArray[i] == 0) && (m_xArray[0] == 1)) //Left side is selected, remove highlights
		{
			if (i == 0)
			{
				m_cannonIcon->SetHovering(false);
				m_cannonInfo->SetActive(false);
			}
			if (i == 1)
			{
				m_movementIcon->SetHovering(false);
				m_movementInfo->SetActive(false);
			}
			if (i == 2)
			{
				m_resourceIcon->SetHovering(false);
				m_resourceInfo->SetActive(false);
			}
		}
		else if (m_xArray[1] == 1 && m_yArray[i] == 1) //Right side is selected, set highlights
		{
			if (i == 0)
			{
				m_shieldIcon->SetHovering(true);
				m_shieldInfo->SetActive(true);
			}
			if (i == 1)
			{
				m_repairIcon->SetHovering(true);
				m_healthInfo->SetActive(true);
			}
			if (i == 2)
			{
				m_plunderIcon->SetHovering(true);
				m_plunderInfo->SetActive(true);
			}
		}
		else if ((m_yArray[i] == 0) && (m_xArray[1] == 1)) //Right side selected, remove highlights
		{
			if (i == 0)
			{
				m_shieldIcon->SetHovering(false);
				m_shieldInfo->SetActive(false);
			}
			if (i == 1)
			{
				m_repairIcon->SetHovering(false);
				m_healthInfo->SetActive(false);
			}
			if (i == 2)
			{
				m_plunderIcon->SetHovering(false);
				m_plunderInfo->SetActive(false);
			}
			m_cannonIcon->SetHovering(false);
			m_cannonInfo->SetActive(false);
			m_movementIcon->SetHovering(false);
			m_movementInfo->SetActive(false);
			m_resourceIcon->SetHovering(false);
			m_resourceInfo->SetActive(false);
		}
	}
}

