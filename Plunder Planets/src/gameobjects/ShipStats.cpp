#include "ShipStats.h"
ShipStats* ShipStats::s_playerStats;
unsigned int ShipStats::s_currentLevel;

ShipStats::ShipStats()
{
	m_cannonDamage = 5;
	//m_cannonSpread; //Add later
	//m_cannonQuantity; //Add later
	m_speed = 50;
	m_boostCost = 20;
	m_cannonCost = 50;
	m_shieldAmount = 0;
	m_healthAmount = 1;
	m_placeHolderHealthAmount = 1;
	m_plunderSpeed = 0.5f;
	s_currentLevel = 1;
}

float ShipStats::GetSpeed()
{
	return m_speed;
}

float ShipStats::GetCannonDamage()
{
	return m_cannonDamage;
}

float ShipStats::GetCannonSpread()
{
	return m_cannonSpread;
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

float ShipStats::GetPlunderSpeed()
{
	return m_plunderSpeed;
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

void ShipStats::IncreaseShieldAmount(float talentAmount)
{
	if (talentAmount == 1)
		m_shieldAmount = 0.3;
	else
		m_shieldAmount = 0.3 + (0.175 * (talentAmount-1)); //0.3, 0.475, 0.65, 0.825, 1
	LOG("Shield amount: " + std::to_string(m_shieldAmount));
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

void ShipStats::RepairHealth(float talentAmount)
{
	if (talentAmount == 1)
	{
		m_placeHolderHealthAmount = 1 - m_healthAmount;
		m_healthAmount = 1;
	}
	if (talentAmount == 0)
		m_healthAmount = m_placeHolderHealthAmount;
	LOG("Health Amount: " + std::to_string(m_healthAmount));
}

void ShipStats::IncreasePlunderSpeed(float talentAmount)
{
	if (talentAmount == 5)
		m_plunderSpeed = 15;
	else
		m_plunderSpeed = 5 + (1.25f * talentAmount);
	LOG("Plunder speed: " + std::to_string(m_plunderSpeed));
}
