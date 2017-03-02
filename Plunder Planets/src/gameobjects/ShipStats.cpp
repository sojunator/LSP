#include "ShipStats.h"

ShipStats::ShipStats() : PlayerStats()
{
	m_cannonDamage = 5;
	m_cannonSpread; //Add later
	m_cannonQuantity; //Add later
	m_speed = 1500;
	m_enemySpeed = 600;
	m_boostCost = 20;
	m_cannonCost = 50;
	m_shieldAmount = 0;
}

float ShipStats::GetSpeed()
{
	return m_speed;
}

float ShipStats::GetEnemySpeed()
{
	return m_enemySpeed;
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
	m_cannonDamage = m_cannonDamage + (talentAmount * 2);
}
