#pragma once
#include "Thomas.h"
#include "../../THOMAS/src/utils/DebugTools.h"
#include "../../THOMAS/src/object/component/Camera.h"

using namespace thomas;
using namespace object;

static class ShipStats
{
private:

public:
	ShipStats();
	void SetCurrentGold(float gold);
	void SetCannonDamage(float cannondamage);
	void SetSpeed(float speed);
	void SetBoostCost(float boost);
	void SetCannonCost(float cannonCost);
	void SetShieldAmount(float shield);
	void SetCurrentHealth(float health);
	void LowerCurrentHealth(float healthDifference);
	void SetPlunderSpeed(float plunde);

	float GetTreasure();
	void HardSetTreasure(float gold);
	void SetTreasure(float goldDifference);
	float GetGoldPlacerHolder();
	void SetGoldPlacerHolder(float gold);
	float GetCannonCounter();
	float GetMovementCounter();
	float GetResourceCounter();
	float GetShieldCounter();
	float GetPlunderCounter();
	float GetCannonDamage();
	float GetCannonQuantity();
	float GetSpeed();
	float GetBoostCost();
	float GetCannonCost();
	float GetShieldAmount();
	float GetHealthAmount();
	float GetPlaceholderHealthAmount();
	float GetPlunderSpeed();
	float GetFOV();
	void SetFOV(bool minorplus);
	float GetInvertCamX();
	float GetInvertCamY();
	void SetInvertCamX(bool state);
	void SetInvertCamY(bool state);
	static float IncreaseTotalGold(float gold);
	static float GetTotalGold();

	void IncreaseCannonDamage(float talentAmount);
	//void IncreaseCannonQuantity();
	void IncreaseSpeed(float talentAmount);
	void DecreaseCosts(float talentAmount);
	void IncreaseShieldAmount(float talentAmount);
	void RepairHealth(float talentAmount);
	void IncreasePlunderSpeed(float talentAmount);

	static ShipStats* s_playerStats;
	static unsigned int s_currentLevel;
	static bool s_playerDied;
private:
	static float s_totalgold;
	float m_cannonCounter;
	float m_movementCounter;
	float m_resourceCounter;
	float m_shieldCounter;
	float m_plunderCounter;
	float m_goldPlaceHolder;
	float m_currentGold;
	float m_cannonDamage;
	float m_cannonQuantity;
	float m_speed;
	float m_boostCost;
	float m_cannonCost;
	float m_shieldAmount;
	float m_healthAmount;
	float m_placeHolderHealthAmount;
	float m_plunderSpeed;
	float m_settingsFOV;
	float m_settingsInvertCamX;
	float m_settingsInvertCamY;
	float m_settingsInvertShip;
	float m_settingsCamRotateSpeed;

};