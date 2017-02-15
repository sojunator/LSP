#include "AI.h"

AI::AI()
{
	m_terrainObject = (TerrainObject*)thomas::object::GameObject::Find("TerrainObject");
	m_playerShip = (Ship*)thomas::object::GameObject::Find("Ship");
}

AI::~AI()
{
}

bool AI::OnCollisionCourse(thomas::math::Vector3 pos)
{
	/*if (m_terrainObject->Collision(pos))
	{

	}*/
	return false;
}
