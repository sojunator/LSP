#pragma once

#include "Thomas.h"
#include "ShipStats.h"

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
	void UpdateGoldCounter();
	void UpdateHealthCounter();
	void CannonCheck(bool upgrade, bool undo);
	void MovementCheck(bool upgrade, bool undo);
	void ResourceCheck(bool upgrade, bool undo);
	void ShieldCheck(bool upgrade, bool undo);
	void RepairCheck(bool upgrade, bool undo);
	void PlunderCheck(bool upgrade, bool undo);
	void Navigation();
	void SetSelectedObject();

private:
	component::Camera* fov;
	component::ParticleEmitterComponent* m_wormhole;
	component::SpriteComponent* m_explanation;
	component::SpriteComponent* m_cannonInfo;
	component::SpriteComponent* m_movementInfo;
	component::SpriteComponent* m_resourceInfo;
	component::SpriteComponent* m_shieldInfo;
	component::SpriteComponent* m_healthInfo;
	component::SpriteComponent* m_plunderInfo;
	component::SpriteComponent* m_startButton;
	component::SpriteComponent* m_cannonIcon;
	component::SpriteComponent* m_cannonTalent1;
	component::SpriteComponent* m_cannonTalent2;
	component::SpriteComponent* m_cannonTalent3;
	component::SpriteComponent* m_cannonTalent4;
	component::SpriteComponent* m_cannonTalent5;
	component::SpriteComponent* m_movementIcon;
	component::SpriteComponent* m_movementTalent1;
	component::SpriteComponent* m_movementTalent2;
	component::SpriteComponent* m_movementTalent3;
	component::SpriteComponent* m_movementTalent4;
	component::SpriteComponent* m_movementTalent5;
	component::SpriteComponent* m_resourceIcon;
	component::SpriteComponent* m_resourceTalent1;
	component::SpriteComponent* m_resourceTalent2;
	component::SpriteComponent* m_resourceTalent3;
	component::SpriteComponent* m_resourceTalent4;
	component::SpriteComponent* m_resourceTalent5;
	component::SpriteComponent* m_shieldIcon;
	component::SpriteComponent* m_shieldTalent1;
	component::SpriteComponent* m_shieldTalent2;
	component::SpriteComponent* m_shieldTalent3;
	component::SpriteComponent* m_shieldTalent4;
	component::SpriteComponent* m_shieldTalent5;
	component::SpriteComponent* m_repairIcon;
	component::SpriteComponent* m_repairTalent1;
	component::SpriteComponent* m_plunderIcon;
	component::SpriteComponent* m_plunderTalent1;
	component::SpriteComponent* m_plunderTalent2;
	component::SpriteComponent* m_plunderTalent3;
	component::SpriteComponent* m_plunderTalent4;
	component::SpriteComponent* m_plunderTalent5;
	component::SpriteComponent* m_exitButton;

	component::SoundComponent* m_music;
	component::SoundComponent* m_plunder;

	component::TextComponent* m_currentGold;
	component::TextComponent* m_currentHealth;
	component::TextComponent* m_cannonCosts;
	component::TextComponent* m_movementCosts;
	component::TextComponent* m_resourceCosts;
	component::TextComponent* m_shieldCosts;
	component::TextComponent* m_repairCosts;
	component::TextComponent* m_plunderSpeedCosts;

	//Bool checks for talents
	bool m_cannonCheck[5] = { false };
	bool m_movementCheck[5] = { false };
	bool m_resourceCheck[5] = { false };
	bool m_shieldCheck[5] = { false };
	bool m_repairCheck[1] = { false };
	bool m_plunderCheck[5] = { false };

	int m_yArray[3] = { 1, 0, 0 };	//3 rows
	int m_xArray[2] = { 1, 0 };		//2 columns
	float m_delay = 0.3f;
	float m_upgradeDelay = 0.3f;
	int m_healthRepairCounts = 0;
	int m_refundHolder = 0;

	float m_resourceHolder = 0;
};
