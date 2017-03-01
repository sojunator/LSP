#pragma once
#pragma once

#include <Thomas.h>

using namespace thomas;
using namespace object;
class UpgradeMenuObject : public GameObject
{

private:

public:
	UpgradeMenuObject() : GameObject("UpgradeMenuObject")
	{

	}
	~UpgradeMenuObject()
	{
	}

	void Start();


	void Update();



private:
	component::SpriteComponent* m_header;
	component::SpriteComponent* m_startButton;
	component::SpriteComponent* m_cannonIcon;
	component::SpriteComponent* m_cannonCost;
	component::SpriteComponent* m_cannonTalent1;
	component::SpriteComponent* m_cannonTalent2;
	component::SpriteComponent* m_cannonTalent3;
	component::SpriteComponent* m_cannonTalent4;
	component::SpriteComponent* m_cannonTalent5;
	component::SpriteComponent* m_movementIcon;
	component::SpriteComponent* m_movementCost;;
	component::SpriteComponent* m_movementTalent1;
	component::SpriteComponent* m_movementTalent2;
	component::SpriteComponent* m_movementTalent3;
	component::SpriteComponent* m_movementTalent4;
	component::SpriteComponent* m_movementTalent5;
	component::SpriteComponent* m_resourceIcon;
	component::SpriteComponent* m_resourceCost;
	component::SpriteComponent* m_resourceTalent1;
	component::SpriteComponent* m_resourceTalent2;
	component::SpriteComponent* m_resourceTalent3;
	component::SpriteComponent* m_resourceTalent4;
	component::SpriteComponent* m_resourceTalent5;
	component::SpriteComponent* m_shieldIcon;
	component::SpriteComponent* m_shieldCost;
	component::SpriteComponent* m_shieldTalent1;
	component::SpriteComponent* m_shieldTalent2;
	component::SpriteComponent* m_shieldTalent3;
	component::SpriteComponent* m_shieldTalent4;
	component::SpriteComponent* m_shieldTalent5;
	component::SpriteComponent* m_exitButton;
	component::SpriteComponent* m_backgrounds;
	component::SoundComponent* m_music;

	//Bool checks for talents
	bool m_cannonCheck[4] = { false };
	bool m_movementCheck[4] = { false };
	bool m_resourceCheck[4] = { false };
	bool m_shieldCheck[4] = { false };

};
