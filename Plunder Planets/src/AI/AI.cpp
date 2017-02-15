#include "AI.h"

AI::AI()
{
	m_terrainObject = (TerrainObject*)thomas::object::GameObject::Find("TerrainObject");
}

AI::~AI()
{
}

bool AI::OnCollisionCourse(thomas::math::Vector3 pos)
{
	//m_terrainObject->Collision();
	return false;
}
