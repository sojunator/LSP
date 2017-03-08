#pragma once

#include "../gameobjects/Ship.h"
#include "Pathfinding.h"
#include "Thomas.h"
#include "../../THOMAS/src/object/component/Component.h"

class TerrainObject;
class THOMAS_API AI : public thomas::object::component::Component
{
public:
	enum class State
	{
		Searching,
		Chasing,
		Attacking
	};
public:
	AI();
	void Start();
	void OnEnable();
	void Update();
	void ChasingUpdate();
	void SearchingUpdate();
	void AttackingUpdate();
	float GetDistanceToTarget();
	math::Vector3 GetTargetVector();
	bool LineOfSight(math::Vector3 dir, float maxLength);
	State GetState();
	
	math::Vector3 GetMovePos();
	math::Vector3 GetTargetPos();

private:
	State m_currentState;
	float m_searchRadius;
	float m_fireRadius;
	TerrainObject* m_terrainObject;
	GameObject* m_target;
	math::Vector3 m_lastKnownPos;
	math::Vector3 m_moveToPos;
};
