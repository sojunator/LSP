#pragma once
#include "../gameobjects/TerrainObject.h"
#include "../gameobjects/Ship.h"
#include "Pathfinding.h"
#include "Thomas.h"
#include "../gameobjects/Ship.h"
#include "../../THOMAS/src/object/component/Component.h"

class THOMAS_API AI : public thomas::object::component::Component
{
public:
	enum class Behavior
	{
		Idle,
		Searching,
		Attacking,
		Firing,
	};
public:
	AI();
	~AI();
	
	bool Collision(math::Vector3 pos);
	int TurnDir(math::Vector3  pos, math::Vector3 forward, math::Vector3 right, bool objectFront, bool objectRight, bool objectLeft);
	int FireCannons(math::Vector3 pos, math::Vector3 right);
	void InsideRadius(float radius, math::Vector3 pos, math::Vector3& dir);
	void InsideAttackRadius(float radius, math::Vector3 pos, math::Vector3& dir);
	Behavior GetState();
	void Escape();

private:
	Behavior m_state;
	std::string m_stateStr;
	math::Vector3 m_lastKnownPos;

	float m_escapeTimer;
	float m_escapeTime;

	TerrainObject* m_terrainObject;
	Ship* m_playerShip;

	float pDotR;
	float pDotF;


};