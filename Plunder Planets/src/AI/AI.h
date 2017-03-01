#pragma once

#include "Thomas.h"
#include "../../THOMAS/src/object/component/Component.h"

class TerrainObject;
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
	bool Collision(thomas::math::Vector3 pos);
	int TurnDir(thomas::math::Vector3  pos, thomas::math::Vector3 forward, thomas::math::Vector3 right, bool objectFront, bool objectRight, bool objectLeft);
	int FireCannons(thomas::math::Vector3 pos, thomas::math::Vector3 right);
	void InsideRadius(float radius, thomas::math::Vector3 pos, thomas::math::Vector3& dir);
	void InsideAttackRadius(float radius, thomas::math::Vector3 pos, thomas::math::Vector3& dir);
	Behavior GetState();
	void Escape();
	void IdleTimer();

	thomas::math::Vector3 GetTargetPos();
	thomas::math::Vector3 GetTargetForward();

private:
	Behavior m_state;
	std::string m_stateStr;
	thomas::math::Vector3 m_lastKnownPos;

	float m_escapeTimer;
	float m_escapeTime;

	float m_idleTimer;
	float m_idleTime;

	TerrainObject* m_terrainObject;
	thomas::object::GameObject* m_playerShip;
	std::vector<thomas::object::GameObject*> m_enemies;

	float pDotR;
	float pDotF;
};
