#include "ShipStats.h"
ShipStats* ShipStats::s_playerStats;

ShipStats::ShipStats()
{

	m_cannonDamage = 5;
	//m_cannonSpread; //Add later
	//m_cannonQuantity; //Add later
	m_speed = 150;
	m_boostCost = 20;
	m_cannonCost = 50;
	m_shieldAmount = 0;
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

void ShipStats::IncreaseCannonDamage(float talentAmount)
{
	m_cannonDamage = 5 + (talentAmount * 2);
	LOG(m_cannonDamage);
}

void ShipStats::IncreaseSpeed(float talentAmount)
{
	m_speed = 150 + (talentAmount * 30);
	LOG(m_speed);
}