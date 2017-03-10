#include "ShipStats.h"
ShipStats* ShipStats::s_playerStats;
unsigned int ShipStats::s_currentLevel;
float ShipStats::s_totalgold;
bool ShipStats::s_playerDied;

ShipStats::ShipStats()
{
	m_currentGold = 1000;
	m_cannonDamage = 5;
	//m_cannonQuantity; //Add later
	m_speed = 50;
	m_boostCost = 20;
	m_cannonCost = 50;
	m_shieldAmount = 0;
	m_healthAmount = 1;
	m_placeHolderHealthAmount = 1;
	m_plunderSpeed = 30;
	m_settingsFOV = 50;
	m_settingsInvertCamX = -1;
	m_settingsInvertCamY = -1;
	m_settingsInvertShip = 0;
	m_settingsCamRotateSpeed = 0;
	s_currentLevel = 0;
}

void ShipStats::SetCurrentGold(float gold)
{
	m_currentGold = gold;
}

void ShipStats::SetCannonDamage(float cannondamage)
{
	m_cannonDamage = cannondamage;
}

void ShipStats::SetSpeed(float speed)
{
	m_speed = speed;
}

void ShipStats::SetBoostCost(float boost)
{
	m_boostCost = boost;
}

void ShipStats::SetCannonCost(float cannonCost)
{
	m_cannonCost = cannonCost;
}

void ShipStats::SetShieldAmount(float shield)
{
	m_shieldAmount = shield;
}

void ShipStats::SetCurrentHealth(float health)
{
	m_healthAmount = health;
	m_placeHolderHealthAmount = health;
}

void ShipStats::SetPlunderSpeed(float plunder)
{
	m_plunderSpeed = plunder;
}


float ShipStats::GetTreasure()
{
	return m_currentGold;
}

void ShipStats::SetTreasure(float goldDifference)
{
	m_currentGold = m_currentGold + goldDifference;
}

float ShipStats::GetCannonDamage()
{
	return m_cannonDamage;
}

float ShipStats::GetSpeed()
{
	return m_speed;
}

float ShipStats::GetCannonQuantity()
{
	return m_cannonQuantity;
}

float ShipStats::GetCannonCost()
{
	return m_cannonCost;
}

float ShipStats::GetBoostCost()
{
	return m_boostCost;
}

float ShipStats::GetShieldAmount()
{
	return m_shieldAmount;
}

float ShipStats::GetHealthAmount()
{
	return m_healthAmount;
}

float ShipStats::GetPlaceholderHealthAmount()
{
	return m_placeHolderHealthAmount;
}

float ShipStats::GetPlunderSpeed()
{
	return m_plunderSpeed;
}

float ShipStats::GetFOV()
{
	return m_settingsFOV;
}

void ShipStats::SetFOV(bool minorplus)
{
	if (minorplus)
		m_settingsFOV += 10;
	else
		m_settingsFOV -= 10;
}

float ShipStats::GetInvertCamX()
{
	return m_settingsInvertCamX;
}

float ShipStats::GetInvertCamY()
{
	return m_settingsInvertCamY;
}

void ShipStats::SetInvertCamX(bool state)
{
	if (state)
		m_settingsInvertCamX = 1;
	else
		m_settingsInvertCamX = -1;
}

void ShipStats::SetInvertCamY(bool state)
{
	if (state)
		m_settingsInvertCamY = 1;
	else
		m_settingsInvertCamY = -1;
}

float ShipStats::IncreaseTotalGold(float gold)
{
	s_totalgold += gold;
	return gold; // We need to use this again later
}

float ShipStats::GetTotalGold()
{
	return s_totalgold;
}


void ShipStats::IncreaseCannonDamage(float talentAmount)
{
	m_cannonDamage = 5 + (talentAmount * 2);
	LOG("Cannon damage: " + std::to_string(m_cannonDamage));
}

void ShipStats::IncreaseSpeed(float talentAmount)
{
	if (talentAmount == 5)
		m_speed = 200;
	else
		m_speed = 50 + (talentAmount * 25); //50, 75, 100, 125, 150
	LOG("Speed: " + std::to_string(m_speed));
}

void ShipStats::DecreaseCosts(float talentAmount)
{
	if (talentAmount == 5)
	{
		m_cannonCost = 20;
		m_boostCost = 5;
	}
	else
	{
		m_cannonCost = 50 - (5 * talentAmount); //50, 45, 40, 35, 30
		m_boostCost = 20 - (2.5f * talentAmount); //20, 17.5, 15, 12.5, 10
	}
	LOG("Cannon cost: " + std::to_string(m_cannonCost));
	LOG("Boost cost: " + std::to_string(m_boostCost));
}

void ShipStats::IncreaseShieldAmount(float talentAmount)
{
	if (talentAmount == 1)
		m_shieldAmount = 0.3;
	else
		m_shieldAmount = 0.3 + (0.175 * (talentAmount - 1)); //0.3, 0.475, 0.65, 0.825, 1
	LOG("Shield amount: " + std::to_string(m_shieldAmount));
}

void ShipStats::RepairHealth(float talentAmount)
{
	if (talentAmount == 1 && m_healthAmount <= 0.75)
	{
		m_healthAmount += 0.25;
		/*m_placeHolderHealthAmount = 1 - m_healthAmount;
		m_healthAmount = 1;*/
	}
	else if (talentAmount == 1 && m_healthAmount > 0.75)
	{
		m_placeHolderHealthAmount = 1 - m_healthAmount;
		m_healthAmount = 1;
	}
	else if (talentAmount == 0)
	{
		m_placeHolderHealthAmount = 0.25;
		m_healthAmount -= 0.25;
		//m_healthAmount = m_placeHolderHealthAmount;
	}
	LOG("Health Amount: " + std::to_string(m_healthAmount));
}

void ShipStats::IncreasePlunderSpeed(float talentAmount)
{
	if (talentAmount == 5)
		m_plunderSpeed = 250;
	else
		m_plunderSpeed = 30 + (30 * talentAmount); //30, 60, 90, 120, 150
	LOG("Plunder speed: " + std::to_string(m_plunderSpeed));
}