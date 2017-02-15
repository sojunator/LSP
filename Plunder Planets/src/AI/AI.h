#pragma once
#include "../gameobjects/TerrainObject.h"
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
	//int 

private:
	Pathfinding pathfinding;
	TerrainObject* m_terrainObject;

};
