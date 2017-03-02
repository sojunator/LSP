#include "ShipStats.h"
ShipStats* ShipStats::s_playerStats;
ShipStats::ShipStats(int shipType)
{
	if (shipType == 0)
	{
		m_cannonDamage = 5;
		//m_cannonSpread; //Add later
		//m_cannonQuantity; //Add later
		m_speed = 1500;
		m_boostCost = 20;
		m_cannonCost = 50;
		m_shieldAmount = 0;
	}
	if (shipType == 1)
	{
		m_cannonDamage = 5;
		//m_cannonSpread; //Add later
		//m_cannonQuantity; //Add later
		m_speed = 600;
		//m_boostCost = 20;
		//m_cannonCost = 50;
		//m_shieldAmount = 0;
	}
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

//ShipStats* ShipStats::GetPlayerStats()
//{
//	return s_playerStats;
//}
//
//void ShipStats::SetPlayerStats(ShipStats* shipType)
//{
//	s_playerStats = shipType;
//}