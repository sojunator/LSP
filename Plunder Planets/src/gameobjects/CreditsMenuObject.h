#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;

class CreditsMenuObject : public GameObject
{
private:
public:
	CreditsMenuObject() : GameObject("CreditsMenuObject")
	{

	}
	~CreditsMenuObject()
	{
	}

	void Start();
	void Update();

private:
	component::SpriteComponent* m_background;
	component::SpriteComponent* m_exitButton;

	component::TextComponent* m_creditsHead;
	component::TextComponent* m_creditsBoys;
	component::TextComponent* m_creditsDevelopers;
	component::TextComponent* m_morgan;
	component::TextComponent* m_gustav;
	component::TextComponent* m_albin;
	component::TextComponent* m_nick;
	component::TextComponent* m_oskar;
	component::TextComponent* m_carol;
	component::TextComponent* m_jakob;

	component::SoundComponent* m_music;

};