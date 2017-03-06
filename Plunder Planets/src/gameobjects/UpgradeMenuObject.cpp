#include "UpgradeMenuObject.h"
#include "../scenes/GameScene.h"
#include "ShipStats.h"
void UpgradeMenuObject::Start()
{
	component::Camera* cam = AddComponent<component::Camera>();
	m_header = AddComponent<component::SpriteComponent>();
	m_startButton = AddComponent<component::SpriteComponent>();
	m_cannonIcon = AddComponent<component::SpriteComponent>();
	m_cannonCost = AddComponent<component::SpriteComponent>();
	m_cannonTalent1 = AddComponent<component::SpriteComponent>();
	m_cannonTalent2 = AddComponent<component::SpriteComponent>();
	m_cannonTalent3 = AddComponent<component::SpriteComponent>();
	m_cannonTalent4 = AddComponent<component::SpriteComponent>();
	m_cannonTalent5 = AddComponent<component::SpriteComponent>();
	m_movementIcon = AddComponent<component::SpriteComponent>();
	m_movementCost = AddComponent<component::SpriteComponent>();
	m_movementTalent1 = AddComponent<component::SpriteComponent>();
	m_movementTalent2 = AddComponent<component::SpriteComponent>();
	m_movementTalent3 = AddComponent<component::SpriteComponent>();
	m_movementTalent4 = AddComponent<component::SpriteComponent>();
	m_movementTalent5 = AddComponent<component::SpriteComponent>();
	m_resourceIcon = AddComponent<component::SpriteComponent>();
	m_resourceCost = AddComponent<component::SpriteComponent>();
	m_resourceTalent1 = AddComponent<component::SpriteComponent>();
	m_resourceTalent2 = AddComponent<component::SpriteComponent>();
	m_resourceTalent3 = AddComponent<component::SpriteComponent>();
	m_resourceTalent4 = AddComponent<component::SpriteComponent>();
	m_resourceTalent5 = AddComponent<component::SpriteComponent>();
	m_shieldIcon = AddComponent<component::SpriteComponent>();
	m_shieldCost = AddComponent<component::SpriteComponent>();
	m_shieldTalent1 = AddComponent<component::SpriteComponent>();
	m_shieldTalent2 = AddComponent<component::SpriteComponent>();
	m_shieldTalent3 = AddComponent<component::SpriteComponent>();
	m_shieldTalent4 = AddComponent<component::SpriteComponent>();
	m_shieldTalent5 = AddComponent<component::SpriteComponent>();
	m_repairIcon = AddComponent<component::SpriteComponent>();
	m_repairCost = AddComponent<component::SpriteComponent>();
	m_repairTalent1 = AddComponent<component::SpriteComponent>();
	m_plunderIcon = AddComponent<component::SpriteComponent>();
	m_plunderCost = AddComponent<component::SpriteComponent>();
	m_plunderTalent1 = AddComponent<component::SpriteComponent>();
	m_plunderTalent2 = AddComponent<component::SpriteComponent>();
	m_plunderTalent3 = AddComponent<component::SpriteComponent>();
	m_plunderTalent4 = AddComponent<component::SpriteComponent>();
	m_plunderTalent5 = AddComponent<component::SpriteComponent>(); 
	m_exitButton = AddComponent<component::SpriteComponent>();
	m_music = AddComponent<component::SoundComponent>();
	m_wormhole = AddComponent<component::ParticleEmitterComponent>();

	m_music->SetClip("mMenuTheme");
	m_music->SetLooping(true);
	m_music->Play();

	m_header->SetName("Header");
	m_header->SetPositionX(722);
	m_header->SetPositionY(20);
	m_header->SetScale(math::Vector2(2.0f, 2.0f));
	m_header->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_header->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_header->SetInteractable(false);

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

	m_cannonCost->SetName("CannonCost");
	m_cannonCost->SetPositionX(50);
	m_cannonCost->SetPositionY(150);
	m_cannonCost->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonCost->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonCost->SetHoverColor(math::Color(1.0, 1.0, 1.0));
	m_cannonCost->SetInteractable(false);

	m_cannonTalent1->SetName("CannonTalent1");
	m_cannonTalent1->SetPositionX(220);
	m_cannonTalent1->SetPositionY(250);
	m_cannonTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent1->SetInteractable(false);

	m_cannonTalent2->SetName("CannonTalent2");
	m_cannonTalent2->SetPositionX(285);
	m_cannonTalent2->SetPositionY(250);
	m_cannonTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent2->SetInteractable(false);

	m_cannonTalent3->SetName("CannonTalent3");
	m_cannonTalent3->SetPositionX(350);
	m_cannonTalent3->SetPositionY(250);
	m_cannonTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent3->SetInteractable(false);

	m_cannonTalent4->SetName("CannonTalent4");
	m_cannonTalent4->SetPositionX(415);
	m_cannonTalent4->SetPositionY(250);
	m_cannonTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent4->SetInteractable(false);

	m_cannonTalent5->SetName("CannonTalent5");
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

	m_movementCost->SetName("MovementCost");
	m_movementCost->SetPositionX(50);
	m_movementCost->SetPositionY(375);
	m_movementCost->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementCost->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementCost->SetHoverColor(math::Color(1.0, 1.0, 1.0));
	m_movementCost->SetInteractable(false);

	m_movementTalent1->SetName("MovementTalent1");
	m_movementTalent1->SetPositionX(220);
	m_movementTalent1->SetPositionY(475);
	m_movementTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent1->SetInteractable(false);

	m_movementTalent2->SetName("MovementTalent2");
	m_movementTalent2->SetPositionX(285);
	m_movementTalent2->SetPositionY(475);
	m_movementTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent2->SetInteractable(false);

	m_movementTalent3->SetName("MovementTalent3");
	m_movementTalent3->SetPositionX(350);
	m_movementTalent3->SetPositionY(475);
	m_movementTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent3->SetInteractable(false);

	m_movementTalent4->SetName("MovementTalent4");
	m_movementTalent4->SetPositionX(415);
	m_movementTalent4->SetPositionY(475);
	m_movementTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent4->SetInteractable(false);

	m_movementTalent5->SetName("MovementTalent5");
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

	m_resourceCost->SetName("ResourceCost");
	m_resourceCost->SetPositionX(50);
	m_resourceCost->SetPositionY(600);
	m_resourceCost->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceCost->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceCost->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceCost->SetInteractable(false);

	m_resourceTalent1->SetName("ResourceTalent1");
	m_resourceTalent1->SetPositionX(220);
	m_resourceTalent1->SetPositionY(700);
	m_resourceTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent1->SetInteractable(false);

	m_resourceTalent2->SetName("ResourceTalent2");
	m_resourceTalent2->SetPositionX(285);
	m_resourceTalent2->SetPositionY(700);
	m_resourceTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent2->SetInteractable(false);

	m_resourceTalent3->SetName("ResourceTalent3");
	m_resourceTalent3->SetPositionX(350);
	m_resourceTalent3->SetPositionY(700);
	m_resourceTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent3->SetInteractable(false);

	m_resourceTalent4->SetName("ResourceTalent4");
	m_resourceTalent4->SetPositionX(415);
	m_resourceTalent4->SetPositionY(700);
	m_resourceTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent4->SetInteractable(false);

	m_resourceTalent5->SetName("ResourceTalent5");
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

	m_shieldCost->SetName("ShieldCost");
	m_shieldCost->SetPositionX(1720);
	m_shieldCost->SetPositionY(150);
	m_shieldCost->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldCost->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldCost->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldCost->SetInteractable(false);

	m_shieldTalent1->SetName("ShieldTalent1");
	m_shieldTalent1->SetPositionX(1600);
	m_shieldTalent1->SetPositionY(225);
	m_shieldTalent1->SetScale(math::Vector2(2.0f, 2.0f));
	m_shieldTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent1->SetInteractable(false);

	m_shieldTalent2->SetName("ShieldTalent2");
	m_shieldTalent2->SetPositionX(1535);
	m_shieldTalent2->SetPositionY(250);
	m_shieldTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent2->SetInteractable(false);

	m_shieldTalent3->SetName("ShieldTalent3");
	m_shieldTalent3->SetPositionX(1470);
	m_shieldTalent3->SetPositionY(250);
	m_shieldTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent3->SetInteractable(false);

	m_shieldTalent4->SetName("ShieldTalent4");
	m_shieldTalent4->SetPositionX(1405);
	m_shieldTalent4->SetPositionY(250);
	m_shieldTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent4->SetInteractable(false);

	m_shieldTalent5->SetName("ShieldTalent5");
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

	m_repairCost->SetName("RepairCost");
	m_repairCost->SetPositionX(1720);
	m_repairCost->SetPositionY(375);
	m_repairCost->SetScale(math::Vector2(1.0f, 1.0f));
	m_repairCost->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_repairCost->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_repairCost->SetInteractable(false);

	m_repairTalent1->SetName("RepairTalent1");
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

	m_plunderCost->SetName("PlunderCost");
	m_plunderCost->SetPositionX(1720);
	m_plunderCost->SetPositionY(600);
	m_plunderCost->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderCost->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderCost->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderCost->SetInteractable(false);

	m_plunderTalent1->SetName("PlunderTalent1");
	m_plunderTalent1->SetPositionX(1650);
	m_plunderTalent1->SetPositionY(700);
	m_plunderTalent1->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent1->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent1->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent1->SetInteractable(false);

	m_plunderTalent2->SetName("PlunderTalent2");
	m_plunderTalent2->SetPositionX(1585);
	m_plunderTalent2->SetPositionY(700);
	m_plunderTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent2->SetInteractable(false);

	m_plunderTalent3->SetName("PlunderTalent3");
	m_plunderTalent3->SetPositionX(1520);
	m_plunderTalent3->SetPositionY(700);
	m_plunderTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent3->SetInteractable(false);

	m_plunderTalent4->SetName("PlunderTalent4");
	m_plunderTalent4->SetPositionX(1455);
	m_plunderTalent4->SetPositionY(700);
	m_plunderTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_plunderTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_plunderTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_plunderTalent4->SetInteractable(false);

	m_plunderTalent5->SetName("PlunderTalent5");
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
	
	SetSelectedObject();
	
	if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space) || Input::GetButtonDown(Input::Buttons::B) || Input::GetKeyDown(Input::Keys::Back))
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
	}

	Navigation();
	
	if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK))
		ThomasCore::Exit();

	if (Input::GetKeyDown(Input::Keys::Enter) || Input::GetButtonDown(Input::Buttons::START))
		Scene::LoadScene<GameScene>();
}



void UpgradeMenuObject::CannonCheck(bool upgrade, bool undo)
{
	if (m_cannonIcon->isHovering())
	{
		if (!m_cannonCheck[0] || (undo && !m_cannonCheck[1])) //First time choosing to upgrade Cannon
		{
			if (upgrade)
			{
				m_cannonTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[0] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(1); //Increase Cannon Dmg/Spread/Quantity first time
			}
			else if (undo) //Doesn't need an if(undo), could just be else, but more clear what is happening this way
			{
				m_cannonTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[0] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(0); //Undo first upgrade
			}
		}
		else if (m_cannonCheck[0] && !m_cannonCheck[1] || (undo && !m_cannonCheck[2]))
		{
			if (upgrade)
			{
				m_cannonTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[1] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(2);//Increase Cannon Dmg/Spread/Quantity second time
			}
			else if (undo)
			{
				m_cannonTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[1] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(1);//Undo second upgrade
			}
		}
		else if (m_cannonCheck[1] && !m_cannonCheck[2] || (undo && !m_cannonCheck[3]))
		{
			if (upgrade)
			{
				m_cannonTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[2] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(3);//Increase Cannon Dmg/Spread/Quantity third time
			}
			else if (undo)
			{
				m_cannonTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[2] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(2);//Undo third upgrade
			}
		}
		else if (m_cannonCheck[2] && !m_cannonCheck[3] || (undo && !m_cannonCheck[4]))
		{
			if (upgrade)
			{
				m_cannonTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[3] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(4);//Increase Cannon Dmg/Spread/Quantity fourth time
			}
			else if (undo)
			{
				m_cannonTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[3] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(3);//Undo fourth upgrade
			}
		}
		else if (m_cannonCheck[3] || (undo && m_cannonCheck[4]))
		{
			if (upgrade)
			{
				m_cannonTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[4] = true;
				ShipStats::s_playerStats->IncreaseCannonDamage(5);//Increase Cannon Dmg/Spread/Quantity fifth time
				//Shoot double projectiles
			}
			else if (undo)
			{
				m_cannonTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_cannonCheck[4] = false;
				ShipStats::s_playerStats->IncreaseCannonDamage(4);//Undo fifth upgrade
			}
		}
	}
}

void UpgradeMenuObject::MovementCheck(bool upgrade, bool undo)
{
	if (m_movementIcon->isHovering())
	{
		if (!m_movementCheck[0] || (undo && !m_movementCheck[1])) //First time choosing to upgrade Movement
		{
			if (upgrade)
			{
				m_movementTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[0] = true;
				ShipStats::s_playerStats->IncreaseSpeed(1);//Increase movement speed first time
			}
			if (undo)
			{
				m_movementTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[0] = false;
				ShipStats::s_playerStats->IncreaseSpeed(0);//Undo first movement upgrade
			}
		}
		else if (m_movementCheck[0] && !m_movementCheck[1] || (undo && !m_movementCheck[2]))
		{
			if (upgrade)
			{
				m_movementTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[1] = true;
				ShipStats::s_playerStats->IncreaseSpeed(2);//Increase movement speed second time
			}
			if (undo)
			{
				m_movementTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[1] = false;
				ShipStats::s_playerStats->IncreaseSpeed(1);//Undo second movement upgrade
			}
		}
		else if (m_movementCheck[1] && !m_movementCheck[2] || (undo && !m_movementCheck[3]))
		{
			if (upgrade)
			{
				m_movementTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[2] = true;
				ShipStats::s_playerStats->IncreaseSpeed(3);//Increase movement speed third time
			}
			if (undo)
			{
				m_movementTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[2] = false;
				ShipStats::s_playerStats->IncreaseSpeed(2);//Undo third movement upgrade
			}
		}
		else if (m_movementCheck[2] && !m_movementCheck[3] || (undo && !m_movementCheck[4]))
		{
			if (upgrade)
			{
				m_movementTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[3] = true;
				ShipStats::s_playerStats->IncreaseSpeed(4);//Increase movement speed fourth time
			}
			if (undo)
			{
				m_movementTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[3] = false;
				ShipStats::s_playerStats->IncreaseSpeed(3);//Undo fourth movement upgrade
			}
		}
		else if (m_movementCheck[3] || (undo && m_movementCheck[4]))
		{
			if (upgrade)
			{
				m_movementTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[4] = true;
				ShipStats::s_playerStats->IncreaseSpeed(5);//Increase movement speed fifth time
			}
			if (undo)
			{
				m_movementTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_movementCheck[4] = false;
				ShipStats::s_playerStats->IncreaseSpeed(4);//Undo fifth movement upgrade
			}
		}
	}
}

void UpgradeMenuObject::ResourceCheck(bool upgrade, bool undo)
{
	if (m_resourceIcon->isHovering())
	{
		if (!m_resourceCheck[0] || (undo && !m_resourceCheck[1])) //First time choosing to upgrade Resource Cost Reduction
		{
			if (upgrade)
			{
				m_resourceTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[0] = true;
				//Decrease resource costs first time
			}
			else if (undo)
			{
				m_resourceTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[0] = false;
				//Undo first resource cost reduction
			}
		}
		else if (m_resourceCheck[0] && !m_resourceCheck[1] || (undo && !m_resourceCheck[2]))
		{
			if (upgrade)
			{
				m_resourceTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[1] = true;
				//Decrease resource costs second time
			}
			else if (undo)
			{
				m_resourceTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[1] = false;
				//Undo second resource cost reduction
			}
		}
		else if (m_resourceCheck[1] && !m_resourceCheck[2] || (undo && !m_resourceCheck[3]))
		{
			if (upgrade)
			{
				m_resourceTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[2] = true;
				//Decrease resource costs third time
			}
			else if (undo)
			{
				m_resourceTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[2] = false;
				//Undo third resource cost reduction
			}
		}
		else if (m_resourceCheck[2] && !m_resourceCheck[3] || (undo && !m_resourceCheck[4]))
		{
			if (upgrade)
			{
				m_resourceTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[3] = true;
				//Decrease resource costs fourth time
			}
			else if (undo)
			{
				m_resourceTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[3] = false;
				//Undo fourth resource cost reduction
			}
		}
		else if (m_resourceCheck[3] || (undo && m_resourceCheck[4]))
		{
			if (upgrade)
			{
				m_resourceTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[4] = true;
				//Decrease resource costs fifth time
			}
			else if (undo)
			{
				m_resourceTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_resourceCheck[4] = false;
				//Undo fifth resource cost reduction
			}
		}
	}
}

void UpgradeMenuObject::ShieldCheck(bool upgrade, bool undo)
{
	if (m_shieldIcon->isHovering())
	{
		if (!m_shieldCheck[0] || (undo && !m_shieldCheck[1])) //First time choosing to upgrade Shield
		{
			if (upgrade)
			{
				m_shieldTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[0] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(1);//Buy Shield
			}
			else if (undo)
			{
				m_shieldTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[0] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(0);//Undo last shield upgrade
			}
		}
		else if (m_shieldCheck[0] && !m_shieldCheck[1] || (undo && !m_shieldCheck[2]))
		{
			if (upgrade)
			{
				m_shieldTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[1] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(2);//Buy Shield
			}
			else if (undo)
			{
				m_shieldTalent2->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[1] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(1);//Undo last shield upgrade
			}
		}
		else if (m_shieldCheck[1] && !m_shieldCheck[2] || (undo && !m_shieldCheck[3]))
		{
			if (upgrade)
			{
				m_shieldTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[2] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(3);//Buy Shield
			}
			else if (undo)
			{
				m_shieldTalent3->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[2] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(2);//Undo last shield upgrade
			}
		}
		else if (m_shieldCheck[2] && !m_shieldCheck[3] || (undo && !m_shieldCheck[4]))
		{
			if (upgrade)
			{
				m_shieldTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[3] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(4);//Buy Shield
			}
			else if (undo)
			{
				m_shieldTalent4->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[3] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(3);//Undo last shield upgrade
			}
		}
		else if (m_shieldCheck[3] || (undo && m_shieldCheck[4]))
		{
			if (upgrade)
			{
				m_shieldTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[4] = true;
				ShipStats::s_playerStats->IncreaseShieldAmount(5);//Buy Shield
			}
			else if (undo)
			{
				m_shieldTalent5->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				m_shieldCheck[4] = false;
				ShipStats::s_playerStats->IncreaseShieldAmount(4);//Undo last shield upgrade
			}
		}
	}
}

void UpgradeMenuObject::RepairCheck(bool upgrade, bool undo)
{
	if (m_repairIcon->isHovering())
	{
		if (!m_repairCheck[0] || (m_repairCheck[0] && undo)) //If upgrading or undoing
		{
			if (upgrade)
			{
				m_repairTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				//Repair health
			}
			else if (undo)
			{
				m_repairTalent1->SetColor(math::Vector4(1.0, 1.0, 1.0, 1));
				//Reset health
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
				m_cannonIcon->SetHovering(true);
			if (i == 1)
				m_movementIcon->SetHovering(true);
			if (i == 2)
				m_resourceIcon->SetHovering(true);

			m_shieldIcon->SetHovering(false);
			m_repairIcon->SetHovering(false);
			m_plunderIcon->SetHovering(false);
		}
		else if ((m_yArray[i] == 0) && (m_xArray[0] == 1)) //Left side is selected, remove highlights
		{
			if (i == 0)
				m_cannonIcon->SetHovering(false);
			if (i == 1)
				m_movementIcon->SetHovering(false);
			if (i == 2)
				m_resourceIcon->SetHovering(false);
			m_shieldIcon->SetHovering(false);
		}
		else if (m_xArray[1] == 1 && m_yArray[i] == 1) //Right side is selected, set highlights
		{
			if (i == 0)
				m_shieldIcon->SetHovering(true);
			if (i == 1)
				m_repairIcon->SetHovering(true);
			if (i == 2)
				m_plunderIcon->SetHovering(true);
		}
		else if ((m_yArray[i] == 0) && (m_xArray[1] == 1)) //Right side selected, remove highlights
		{
			if (i == 0)
				m_shieldIcon->SetHovering(false);
			if (i == 1)
				m_repairIcon->SetHovering(false);
			if (i == 2)
				m_plunderIcon->SetHovering(false);
			m_cannonIcon->SetHovering(false);
			m_movementIcon->SetHovering(false);
			m_resourceIcon->SetHovering(false);
		}
	}
}

