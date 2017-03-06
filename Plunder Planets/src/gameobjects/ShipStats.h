#pragma once
#include <Thomas.h>
#include "../../THOMAS/src/utils/DebugTools.h"
//#include"../src/PlayerStats.h"

using namespace thomas;
using namespace object;

static class ShipStats
{
private:

public:
	ShipStats();
	float GetCannonDamage();
	float GetCannonSpread();
	float GetCannonQuantity();
	float GetSpeed();
	float GetBoostCost();
	float GetCannonCost();
	float GetShieldAmount();
	void IncreaseCannonDamage(float talentAmount);
	//void IncreaseCannonSpread();
	//void IncreaseCannonQuantity();
	void IncreaseSpeed(float talentAmount);
	//void DecreaseBoostCost();
	//void DecreaseCannonCost();
	void IncreaseShieldAmount(float talentAmount);
	static ShipStats* s_playerStats;
	static unsigned int s_currentLevel;
private:
	float m_cannonDamage;
	float m_cannonSpread;
	float m_cannonQuantity;
	float m_speed;
	float m_boostCost;
	float m_cannonCost;
	float m_shieldAmount;
};