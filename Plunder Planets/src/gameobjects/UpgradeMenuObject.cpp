#include "UpgradeMenuObject.h"
#include "../scenes/GameScene.h"
void UpgradeMenuObject::Start()
{
	AddComponent<component::Camera>();
	m_backgrounds = AddComponent<component::SpriteComponent>();
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
	m_exitButton = AddComponent<component::SpriteComponent>();
	m_music = AddComponent<component::SoundComponent>();

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
	m_cannonIcon->SetHoverColor(math::Color(1.0, 1.0, 1.0));
	m_cannonIcon->SetInteractable(false);

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
	m_cannonTalent1->SetInteractable(true);

	m_cannonTalent2->SetName("CannonTalent2");
	m_cannonTalent2->SetPositionX(285);
	m_cannonTalent2->SetPositionY(250);
	m_cannonTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent2->SetInteractable(true);

	m_cannonTalent3->SetName("CannonTalent3");
	m_cannonTalent3->SetPositionX(350);
	m_cannonTalent3->SetPositionY(250);
	m_cannonTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent3->SetInteractable(true);

	m_cannonTalent4->SetName("CannonTalent4");
	m_cannonTalent4->SetPositionX(415);
	m_cannonTalent4->SetPositionY(250);
	m_cannonTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_cannonTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent4->SetInteractable(true);

	m_cannonTalent5->SetName("CannonTalent5");
	m_cannonTalent5->SetPositionX(480);
	m_cannonTalent5->SetPositionY(225);
	m_cannonTalent5->SetScale(math::Vector2(2.0f, 2.0f));
	m_cannonTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_cannonTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_cannonTalent5->SetInteractable(true);

	//Create Movement sprites
	m_movementIcon->SetName("MovementIcon");
	m_movementIcon->SetPositionX(50);
	m_movementIcon->SetPositionY(425);
	m_movementIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementIcon->SetInteractable(false);

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
	m_movementTalent1->SetInteractable(true);

	m_movementTalent2->SetName("MovementTalent2");
	m_movementTalent2->SetPositionX(285);
	m_movementTalent2->SetPositionY(475);
	m_movementTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent2->SetInteractable(true);

	m_movementTalent3->SetName("MovementTalent3");
	m_movementTalent3->SetPositionX(350);
	m_movementTalent3->SetPositionY(475);
	m_movementTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent3->SetInteractable(true);

	m_movementTalent4->SetName("MovementTalent4");
	m_movementTalent4->SetPositionX(415);
	m_movementTalent4->SetPositionY(475);
	m_movementTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_movementTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent4->SetInteractable(true);

	m_movementTalent5->SetName("MovementTalent5");
	m_movementTalent5->SetPositionX(480);
	m_movementTalent5->SetPositionY(450);
	m_movementTalent5->SetScale(math::Vector2(2.0f, 2.0f));
	m_movementTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_movementTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_movementTalent5->SetInteractable(true);

	//Create Resource sprites
	m_resourceIcon->SetName("ResourceIcon");
	m_resourceIcon->SetPositionX(50);
	m_resourceIcon->SetPositionY(650);
	m_resourceIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceIcon->SetInteractable(false);

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
	m_resourceTalent1->SetInteractable(true);

	m_resourceTalent2->SetName("ResourceTalent2");
	m_resourceTalent2->SetPositionX(285);
	m_resourceTalent2->SetPositionY(700);
	m_resourceTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent2->SetInteractable(true);

	m_resourceTalent3->SetName("ResourceTalent3");
	m_resourceTalent3->SetPositionX(350);
	m_resourceTalent3->SetPositionY(700);
	m_resourceTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent3->SetInteractable(true);

	m_resourceTalent4->SetName("ResourceTalent4");
	m_resourceTalent4->SetPositionX(415);
	m_resourceTalent4->SetPositionY(700);
	m_resourceTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_resourceTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent4->SetInteractable(true);

	m_resourceTalent5->SetName("ResourceTalent5");
	m_resourceTalent5->SetPositionX(480);
	m_resourceTalent5->SetPositionY(675);
	m_resourceTalent5->SetScale(math::Vector2(2.0f, 2.0f));
	m_resourceTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_resourceTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_resourceTalent5->SetInteractable(true);

	//Create Shield sprites
	m_shieldIcon->SetName("ShieldIcon");
	m_shieldIcon->SetPositionX(1720);
	m_shieldIcon->SetPositionY(200);
	m_shieldIcon->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldIcon->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldIcon->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldIcon->SetInteractable(false);

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
	m_shieldTalent1->SetInteractable(true);

	m_shieldTalent2->SetName("ShieldTalent2");
	m_shieldTalent2->SetPositionX(1535);
	m_shieldTalent2->SetPositionY(250);
	m_shieldTalent2->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent2->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent2->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent2->SetInteractable(true);

	m_shieldTalent3->SetName("ShieldTalent3");
	m_shieldTalent3->SetPositionX(1470);
	m_shieldTalent3->SetPositionY(250);
	m_shieldTalent3->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent3->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent3->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent3->SetInteractable(true);

	m_shieldTalent4->SetName("ShieldTalent4");
	m_shieldTalent4->SetPositionX(1405);
	m_shieldTalent4->SetPositionY(250);
	m_shieldTalent4->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent4->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent4->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent4->SetInteractable(true);

	m_shieldTalent5->SetName("ShieldTalent5");
	m_shieldTalent5->SetPositionX(1340);
	m_shieldTalent5->SetPositionY(250);
	m_shieldTalent5->SetScale(math::Vector2(1.0f, 1.0f));
	m_shieldTalent5->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_shieldTalent5->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_shieldTalent5->SetInteractable(true);

	m_exitButton->SetName("UpgradeMenuExit");
	m_exitButton->SetPositionX(50);
	m_exitButton->SetPositionY(970);
	m_exitButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_exitButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_exitButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_exitButton->SetInteractable(true);

	m_backgrounds->SetName("UpgradeMenuBackground");
	m_backgrounds->SetPositionX(0);
	m_backgrounds->SetPositionY(0);
	m_backgrounds->SetScale(math::Vector2(1.0f, 1.0f));
	m_backgrounds->SetColor(math::Color(1.0f, 1.0f, 1.0f));
}

void UpgradeMenuObject::Update()
{
	if (Input::GetMouseButtonDown(Input::MouseButtons::LEFT))
	{
		if (m_exitButton->isHovering())
			ThomasCore::Exit();

		if (m_startButton->isHovering())
			Scene::LoadScene<GameScene>();


		//Talents stop being interactable after it has been chosen.
		//Nasty code incoming, wall of code
		//Cannon checks
		if (m_cannonTalent1->isHovering())
		{
			m_cannonTalent1->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_cannonTalent1->SetInteractable(false);
			m_cannonCheck[0] = true;
		}

		if (m_cannonTalent2->isHovering() && m_cannonCheck[0])
		{
			m_cannonTalent2->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_cannonTalent2->SetInteractable(false);
			m_cannonCheck[1] = true;
		}

		if (m_cannonTalent3->isHovering() && m_cannonCheck[1])
		{
			m_cannonTalent3->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_cannonTalent3->SetInteractable(false);
			m_cannonCheck[2] = true;
		}

		if (m_cannonTalent4->isHovering() && m_cannonCheck[2])
		{
			m_cannonTalent4->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_cannonTalent4->SetInteractable(false);
			m_cannonCheck[3] = true;
		}

		if (m_cannonTalent5->isHovering() && m_cannonCheck[3])
		{
			m_cannonTalent5->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_cannonTalent5->SetInteractable(false);
		}

		//Movement checks
		if (m_movementTalent1->isHovering())
		{
			m_movementTalent1->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_movementTalent1->SetInteractable(false);
			m_movementCheck[0] = true;
		}

		if (m_movementTalent2->isHovering() && m_movementCheck[0])
		{
			m_movementTalent2->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_movementTalent2->SetInteractable(false);
			m_movementCheck[1] = true;
		}

		if (m_movementTalent3->isHovering() && m_movementCheck[1])
		{
			m_movementTalent3->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_movementTalent3->SetInteractable(false);
			m_movementCheck[2] = true;
		}

		if (m_movementTalent4->isHovering() && m_movementCheck[2])
		{
			m_movementTalent4->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_movementTalent4->SetInteractable(false);
			m_movementCheck[3] = true;
		}

		if (m_movementTalent5->isHovering() && m_movementCheck[3])
		{
			m_movementTalent5->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_movementTalent5->SetInteractable(false);
		}

		//Resource checks
		if (m_resourceTalent1->isHovering())
		{
			m_resourceTalent1->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_resourceTalent1->SetInteractable(false);
			m_resourceCheck[0] = true;
		}

		if (m_resourceTalent2->isHovering() && m_resourceCheck[0])
		{
			m_resourceTalent2->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_resourceTalent2->SetInteractable(false);
			m_resourceCheck[1] = true;
		}

		if (m_resourceTalent3->isHovering() && m_resourceCheck[1])
		{
			m_resourceTalent3->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_resourceTalent3->SetInteractable(false);
			m_resourceCheck[2] = true;
		}

		if (m_resourceTalent4->isHovering() && m_resourceCheck[2])
		{
			m_resourceTalent4->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_resourceTalent4->SetInteractable(false);
			m_resourceCheck[3] = true;
		}

		if (m_resourceTalent5->isHovering() && m_resourceCheck[3])
		{
			m_resourceTalent5->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_resourceTalent5->SetInteractable(false);
		}

		//Shield checks
		if (m_shieldTalent1->isHovering())
		{
			m_shieldTalent1->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_shieldTalent1->SetInteractable(false);
			m_shieldCheck[0] = true;
		}

		if (m_shieldTalent2->isHovering() && m_shieldCheck[0])
		{
			m_shieldTalent2->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_shieldTalent2->SetInteractable(false);
			m_shieldCheck[1] = true;
		}

		if (m_shieldTalent3->isHovering() && m_shieldCheck[1])
		{
			m_shieldTalent3->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_shieldTalent3->SetInteractable(false);
			m_shieldCheck[2] = true;
		}

		if (m_shieldTalent4->isHovering() && m_shieldCheck[2])
		{
			m_shieldTalent4->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_shieldTalent4->SetInteractable(false);
			m_shieldCheck[3] = true;
		}

		if (m_shieldTalent5->isHovering() && m_shieldCheck[3])
		{
			m_shieldTalent5->SetColor(math::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
			m_shieldTalent5->SetInteractable(false);
		}
	}

	if (Input::GetKeyDown(Input::Keys::Escape))
		ThomasCore::Exit();

	if (Input::GetKeyDown(Input::Keys::Enter))
		Scene::LoadScene<GameScene>();
}
