#pragma once
#include "../gameobjects/TerrainObject.h"
#include "../gameobjects/Ship.h"
#include "Pathfinding.h"
#include "Thomas.h"


class AI
{
public:
	enum class Behavior
	{
		Idle,
		Searching,
		Attacking,
	};
public:
	AI();
	~AI();
	
	bool OnCollisionCourse(thomas::math::Vector3 pos);

private:
	Behavior m_state;

	Pathfinding pathfinding;
	TerrainObject* m_terrainObject;
	Ship* m_playerShip;

};
