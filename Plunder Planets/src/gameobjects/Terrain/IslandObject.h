#pragma once
#include "Thomas.h"
#include "../GoldEmitterObject.h"

class PauseObjectMenuObject;
class IslandObject : public thomas::object::GameObject
{
public:
	IslandObject() : thomas::object::GameObject("IslandObject")
	{
	}
	~IslandObject();

	void Start();
	void Update();
	void SetModel(int island);
	void SinkIsland();
	void Looting(bool gotLoot, thomas::math::Vector3 shipPos, GoldEmitterObject* goldEmitter);
	void PlaceRigidBody(float radius, thomas::math::Vector3 center);
	bool CheckDestory();

private:
	thomas::object::component::RenderComponent* m_renderer;
	thomas::object::component::RigidBodyComponent* m_rigidBody;
	static thomas::object::component::SoundComponent* m_sound;
	thomas::object::component::FrustumCullingComponent* m_frustrumCullingComponent;
	thomas::object::component::ParticleEmitterComponent* m_smokeEmitter;
	bool m_falling;
	bool m_destroy;
	float m_radius;
	PauseObjectMenuObject* m_pauseObj;
};