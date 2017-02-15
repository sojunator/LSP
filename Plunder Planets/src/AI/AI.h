#pragma once
#include "../gameobjects/TerrainObject.h"
#include "../gameobjects/Ship.h"
#include "Pathfinding.h"
#include "Thomas.h"
#include "../gameobjects/Ship.h"

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
	
	bool CheckInFront(math::Vector3 pos);
	bool CheckSide(math::Vector3 pos);
	int TurnDir(math::Vector3 pos, math::Vector3 forward);


	void InsideRadius(float radius, math::Vector3 pos, math::Vector3& dir);

	Behavior GetState();

private:
	Behavior m_state;

	math::Vector3 m_lastKnownPos;

	float m_escapeTimer;
	float m_escapeTime;

	Pathfinding* m_pathfinding;
	TerrainObject* m_terrainObject;
	Ship* m_playerShip;

};
