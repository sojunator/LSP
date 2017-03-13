#pragma once

#include "Thomas.h"
using namespace thomas;
using namespace object;
class IslandManager;
class THOMAS_API AI : public component::Component
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
	void SetFireRadius(float radius);

	math::Vector3 GetRandomPos();

private:
	State m_currentState;
	float m_searchRadius;
	float m_fireRadius;
	GameObject* m_target;
	math::Vector3 m_lastKnownPos;
	math::Vector3 m_moveToPos;
};
