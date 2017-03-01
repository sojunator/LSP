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

	m_yArray[0] = 1; //Start with first row selected
	m_xArray[0] = 1; //First column selected

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
	m_delay = m_delay - Time::GetDeltaTime();
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

			m_shieldIcon->SetHovering(false);		//Needs to change if more icons are added in column 2
		}
		else if ((m_yArray[i] == 0) && (m_xArray[0] == 1))
		{
			if (i == 0)
				m_cannonIcon->SetHovering(false);
			if (i == 1)
				m_movementIcon->SetHovering(false);
			if (i == 2)
				m_resourceIcon->SetHovering(false);
			m_shieldIcon->SetHovering(false);
		}
		if (m_xArray[1] == 1) //if more rows added in 2nd column change this, now all left icons lead to shieldIcon when pressing right
		{
			m_shieldIcon->SetHovering(true);
			m_cannonIcon->SetHovering(false);
			m_movementIcon->SetHovering(false);
			m_resourceIcon->SetHovering(false);
		}
	}

	if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space) || Input::GetButtonDown(Input::Buttons::B) || Input::GetKeyDown(Input::Keys::Back))
	{
		bool upgrade = false;
		bool undo = false;
		if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space)) //We decided to upgrade
			upgrade = true;
		if (Input::GetButtonDown(Input::Buttons::B) || Input::GetKeyDown(Input::Keys::Back)) //We decided to undo our upgrade
			undo = true;

		if (m_cannonIcon->isHovering()) //Move into CannonCheck function later
		{
			if (!m_cannonCheck[0]) //First time choosing to upgrade Cannon
			{
				if (upgrade)
				{
					m_cannonTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
					m_cannonCheck[0] = true;
				}
				//Increase Cannon Dmg/Spread/Quantity first time
			}
			else if (m_cannonCheck[0] && !m_cannonCheck[1])
			{
				m_cannonTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[1] = true;
				//Increase Cannon Dmg/Spread/Quantity second time
			}
			else if (m_cannonCheck[1] && !m_cannonCheck[2])
			{
				m_cannonTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[2] = true;
				//Increase Cannon Dmg/Spread/Quantity third time
			}
			else if (m_cannonCheck[2] && !m_cannonCheck[3])
			{
				m_cannonTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_cannonCheck[3] = true;
				//Increase Cannon Dmg/Spread/Quantity fourth time
			}
			else if (m_cannonCheck[3])
			{
				m_cannonTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				//Increase Cannon Dmg/Spread/Quantity fifth time
			}
		}

		if (m_movementIcon->isHovering()) //Move into Movement Check function
		{
			if (!m_movementCheck[0]) //First time choosing to upgrade Movement
			{
				m_movementTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[0] = true;
				//Increase movement speed first time
			}
			else if (m_movementCheck[0] && !m_movementCheck[1])
			{
				m_movementTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[1] = true;
				//Increase movement speed second time
			}
			else if (m_movementCheck[1] && !m_movementCheck[2])
			{
				m_movementTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[2] = true;
				//Increase movement speed third time
			}
			else if (m_movementCheck[2] && !m_movementCheck[3])
			{
				m_movementTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_movementCheck[3] = true;
				//Increase movement speed fourth time
			}
			else if (m_movementCheck[3])
			{
				m_movementTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				//Increase movement speed fifth time
			}
		}
		if (m_resourceIcon->isHovering()) //Move into Resource Check Function
		{
			if (!m_resourceCheck[0]) //First time choosing to upgrade Resource Cost Reduction
			{
				m_resourceTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[0] = true;
				//Decrease resource costs first time
			}
			else if (m_resourceCheck[0] && !m_resourceCheck[1])
			{
				m_resourceTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[1] = true;
				//Decrease resource costs second time
			}
			else if (m_resourceCheck[1] && !m_resourceCheck[2])
			{
				m_resourceTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[2] = true;
				//Decrease resource costs third time
			}
			else if (m_resourceCheck[2] && !m_resourceCheck[3])
			{
				m_resourceTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_resourceCheck[3] = true;
				//Decrease resource costs fourth time
			}
			else if (m_resourceCheck[3])
			{
				m_resourceTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				//Decrease resource costs fifth time
			}
		}
		if (m_shieldIcon->isHovering()) //Move into Shield Check Function
		{
			if (!m_shieldCheck[0]) //First time choosing to upgrade Shield
			{
				m_shieldTalent1->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[0] = true;
				//Buy Shield
			}
			else if (m_shieldCheck[0] && !m_shieldCheck[1])
			{
				m_shieldTalent2->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[1] = true;
				//Upgrade Shield first time
			}
			else if (m_shieldCheck[1] && !m_shieldCheck[2])
			{
				m_shieldTalent3->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[2] = true;
				//Upgrade Shield second time
			}
			else if (m_shieldCheck[2] && !m_shieldCheck[3])
			{
				m_shieldTalent4->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				m_shieldCheck[3] = true;
				//Upgrade Shield third time
			}
			else if (m_shieldCheck[3])
			{
				m_shieldTalent5->SetColor(math::Vector4(0.5, 0.5, 0.5, 1));
				//Upgrade Shield fourth time
			}
		}
	}
	//Menu scrolling, move to own function, LONG if() statement
	if ((Input::GetLeftStickY() && m_delay < 0.1f) || (Input::GetButton(Input::Buttons::DPAD_DOWN) && m_delay < 0.1f)
		|| (Input::GetButton(Input::Buttons::DPAD_UP) && m_delay < 0.1f) || (Input::GetKey(Input::Keys::Down) && m_delay < 0.1f)
		|| (Input::GetKey(Input::Keys::Up) && m_delay < 0.1f) || Input::GetButton(Input::Buttons::DPAD_RIGHT) || Input::GetButton(Input::Buttons::DPAD_LEFT)
		|| Input::GetLeftStickX())
	{
		for (int i = 0; i < 3; i++)
		{
			if ((m_yArray[0] == 1) && (Input::GetLeftStickY() > abs(Input::GetLeftStickX())) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up)) //Player presses up, we're already at the top
			{
				m_yArray[0] = 1;
				break;
			}
			else if ((i > 0) && (m_yArray[i] == 1) && ((Input::GetLeftStickY() > abs(Input::GetLeftStickX())) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up))) //Player presses up
			{
				int x = 0;
				if ((m_xArray[1] == 1) && ((Input::GetLeftStickY() > -(abs(Input::GetLeftStickX()))) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up))) //Player presses up, we're right side, jump to left, continue scrolling
				{
					m_xArray[0] = 1;
					m_xArray[1] = 0;
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
				if ((m_yArray[2] == 1) && ((Input::GetLeftStickY() < -(abs(Input::GetLeftStickX()))) || Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetKey(Input::Keys::Down))) //Player presses down, we're already at the bottom, jump to right side, continue scrolling there
				{
					m_yArray[2] = 1;
					m_xArray[0] = 1;
					m_xArray[1] = 1;
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
	if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK))
		ThomasCore::Exit();

	if (Input::GetKeyDown(Input::Keys::Enter) || Input::GetButtonDown(Input::Buttons::START))
		Scene::LoadScene<GameScene>();
}
