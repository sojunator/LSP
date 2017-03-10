#include "CreditsMenuObject.h"
#include "../scenes/MenuScene.h"

void CreditsMenuObject::Start()
{
	component::Camera* cam = AddComponent<component::Camera>();

	m_background = AddComponent<component::SpriteComponent>();
	m_background->SetName("Background");
	m_background->SetPositionX(0);
	m_background->SetPositionY(0);
	m_background->SetScale(math::Vector2(1.0f, 1.0f));
	m_background->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_background->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_background->SetInteractable(false);

	m_exitButton = AddComponent<component::SpriteComponent>();
	m_exitButton->SetName("Exit");
	m_exitButton->SetPositionX(50);
	m_exitButton->SetPositionY(970);
	m_exitButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_exitButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_exitButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_exitButton->SetInteractable(false);

	m_music = AddComponent<component::SoundComponent>();
	m_music->SetClip("mMenuTheme");
	m_music->SetLooping(true);
	m_music->Play();

	m_creditsHead = AddComponent<component::TextComponent>();
	m_creditsHead->SetFont("Pirate");
	m_creditsHead->SetOutput("Credits");
	m_creditsHead->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_creditsHead->SetRotation(0.0f);
	m_creditsHead->SetScale(2.0f);
	m_creditsHead->SetPositionX((Window::GetWidth() / 2) - 200);
	m_creditsHead->SetPositionY(30);
	m_creditsHead->SetDropshadow(true);
	m_creditsHead->SetOutline(true);
	m_creditsHead->SetOrigin(false);

	m_creditsBoys = AddComponent<component::TextComponent>();
	m_creditsBoys->SetFont("Pirate");
	m_creditsBoys->SetOutput("A Boyzen i Mitten productions");
	m_creditsBoys->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_creditsBoys->SetRotation(0.0f);
	m_creditsBoys->SetScale(1.5f);
	m_creditsBoys->SetPositionX(50);
	m_creditsBoys->SetPositionY(150);
	m_creditsBoys->SetDropshadow(true);
	m_creditsBoys->SetOutline(true);
	m_creditsBoys->SetOrigin(false);

	m_creditsDevelopers = AddComponent<component::TextComponent>();
	m_creditsDevelopers->SetFont("Pirate");
	m_creditsDevelopers->SetOutput("Developers:");
	m_creditsDevelopers->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_creditsDevelopers->SetRotation(0.0f);
	m_creditsDevelopers->SetScale(1.5f);
	m_creditsDevelopers->SetPositionX(50);
	m_creditsDevelopers->SetPositionY(250);
	m_creditsDevelopers->SetDropshadow(true);
	m_creditsDevelopers->SetOutline(true);
	m_creditsDevelopers->SetOrigin(false);

	m_morgan = AddComponent<component::TextComponent>();
	m_morgan->SetFont("Pirate");
	m_morgan->SetOutput("Morgan Cromell");
	m_morgan->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_morgan->SetRotation(0.0f);
	m_morgan->SetScale(1.0f);
	m_morgan->SetPositionX(50);
	m_morgan->SetPositionY(330);
	m_morgan->SetDropshadow(true);
	m_morgan->SetOutline(true);
	m_morgan->SetOrigin(false);

	m_gustav = AddComponent<component::TextComponent>();
	m_gustav->SetFont("Pirate");
	m_gustav->SetOutput("Gustav Ekelund");
	m_gustav->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_gustav->SetRotation(0.0f);
	m_gustav->SetScale(1.0f);
	m_gustav->SetPositionX(50);
	m_gustav->SetPositionY(380);
	m_gustav->SetDropshadow(true);
	m_gustav->SetOutline(true);
	m_gustav->SetOrigin(false);

	m_albin = AddComponent<component::TextComponent>();
	m_albin->SetFont("Pirate");
	m_albin->SetOutput("Albin Sahlbom");
	m_albin->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_albin->SetRotation(0.0f);
	m_albin->SetScale(1.0f);
	m_albin->SetPositionX(50);
	m_albin->SetPositionY(430);
	m_albin->SetDropshadow(true);
	m_albin->SetOutline(true);
	m_albin->SetOrigin(false);

	m_nick = AddComponent<component::TextComponent>();
	m_nick->SetFont("Pirate");
	m_nick->SetOutput("Nick Wedzinga");
	m_nick->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_nick->SetRotation(0.0f);
	m_nick->SetScale(1.0f);
	m_nick->SetPositionX(50);
	m_nick->SetPositionY(480);
	m_nick->SetDropshadow(true);
	m_nick->SetOutline(true);
	m_nick->SetOrigin(false);

	m_oskar = AddComponent<component::TextComponent>();
	m_oskar->SetFont("Pirate");
	m_oskar->SetOutput("Oskar Warnhag");
	m_oskar->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_oskar->SetRotation(0.0f);
	m_oskar->SetScale(1.0f);
	m_oskar->SetPositionX(50);
	m_oskar->SetPositionY(530);
	m_oskar->SetDropshadow(true);
	m_oskar->SetOutline(true);
	m_oskar->SetOrigin(false);

	m_carol = AddComponent<component::TextComponent>();
	m_carol->SetFont("Pirate");
	m_carol->SetOutput("Carl Soystedt");
	m_carol->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_carol->SetRotation(0.0f);
	m_carol->SetScale(1.0f);
	m_carol->SetPositionX(50);
	m_carol->SetPositionY(580);
	m_carol->SetDropshadow(true);
	m_carol->SetOutline(true);
	m_carol->SetOrigin(false);

	m_jakob = AddComponent<component::TextComponent>();
	m_jakob->SetFont("Pirate");
	m_jakob->SetOutput("Jakob Arneteg");
	m_jakob->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_jakob->SetRotation(0.0f);
	m_jakob->SetScale(1.0f);
	m_jakob->SetPositionX(50);
	m_jakob->SetPositionY(630);
	m_jakob->SetDropshadow(true);
	m_jakob->SetOutline(true);
	m_jakob->SetOrigin(false);
}

void CreditsMenuObject::Update()
{
	if (Input::GetButtonDown(Input::Buttons::BACK) || Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::B))
		Scene::LoadScene<MenuScene>();
}