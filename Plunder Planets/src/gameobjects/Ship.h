#pragma once
#include <Thomas.h>
#include <string>
#include <algorithm>
#include "Broadside.h"
#include "WaterObject.h"
#include "ShipFloat.h"
#include "PhysicsObject.h"
#include "../scenes/MenuScene.h"
#include "ShipStats.h"
#include "graphics\GeometryDraw.h"

using namespace thomas;
using namespace object;
class TerrainObject;
class Ship : public GameObject
{

private:
	void Aim(float side, math::Vector2 aimPos);
public:
	Ship() : GameObject("Ship")
	{
	}
	void Start();
	bool GetFreeCamera();
	void ShipMove(float const dt);
	void ShipRotate(float const dt);
	void ShipFly(float const upFactorPitch, float const upFactorRoll, float const left_y, float const dt);
	void ShipFireCannons();
	void ShipAimCannons();
	void DrawAimArc(Broadside* broadside, float angle);
	//cam
	void CameraRotate(float const right_x, float const right_y, float const dt, math::Vector3 const distanceVector);
	void CameraZoom(float const dt);
	

	void PlaySounds(float const dt){}
	void PlunderIsland();
	int GetTreasure();

	void Float(float dt);

	void Update();
	void OnCollision(component::RigidBodyComponent* other);

public:
	bool m_startUpSequence;
	//Health attributes
	float m_health;
	float m_maxHealth;

	//Armor attributes
	float m_armor;
	float m_maxArmor;

private:
	bool m_spawnedWormhole;

	float m_aimDistance;
	float m_roof;
	bool m_moving;
	bool m_turning;
	bool m_flying;
	float m_treasure;
	float m_mass;
	float m_flyTurnSpeed;
	float m_speed;
	float m_turnSpeed;
	int m_flyCost;
	//used for the camera
	bool m_freeCamera;
	float m_elevateCamSpeed;//for moving cam up and down
	float m_camRotationSpeed;
	float m_camZoomSpeed;
	float m_cameraDistance;
	float m_camMinDistanceFromBoat;
	float m_camMaxDistanceFromBoat;
	//used for both
	float m_controlSensitivity;
	bool m_retardControllsOn;

	math::Vector3 m_lookAtPoint;//point slightly above the boat
	math::Vector3 m_lookAtOffset;
	math::Vector3 m_initPosition;	//Is this needed?
	math::Vector3 m_aimPosition;
	math::Vector3 p0;// = m_transform->GetPosition(); //boat pos
	math::Vector3 p3;// = math::Vector3(m_aimPosition.x, m_aimPosition.y, m_aimPosition.z); //aim pos

	math::Vector3 p1;// = p0 /*+ exitVector*/; //vector defining starting direction of projectiles
	math::Vector3 p2;// = p3 + math::Vector3(0, 1, 0)/* * scalar */;

	//components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	component::SoundComponent* m_boostSound;
	component::RigidBodyComponent* m_rigidBody;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterRight1;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterRight2;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterLeft1;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterLeft2;
	component::TextComponent* m_safeToLeave;

	GeometryDraw* m_arc;
	ShipFloat* m_floats[12];
	GameObject* m_cameraObject;
	TerrainObject* m_terrainObject;
	WaterObject* m_waterObject;

	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRight;
	

	int m_modelIndex;

	float m_soundDelay;
	float m_soundDelayLeft;
	bool m_aiming;
	bool m_prevFrame;
	bool m_aimRight;
	bool m_aimLeft;


	std::string m_SFXs[9] = {
		"fCreak1",
		"fCreak2",
		"fCreak3",
		"fCreak4",
		"fDoubleCreak1",
		"fDoubleCreak2",
		"fDoubleCreak3",
		"fSlowCreak1",
		"fSlowCreak2"
	};

	
};