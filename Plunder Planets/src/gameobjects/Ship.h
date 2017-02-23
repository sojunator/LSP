#pragma once
#include <Thomas.h>
#include <string>
#include <algorithm>
#include "Broadside.h"
#include "TerrainObject.h"
#include "WaterObject.h"
#include "ShipFloat.h"
#include "PhysicsObject.h"
#include "../scenes/MenuScene.h"
using namespace thomas;
using namespace object;
class Ship : public GameObject
{

private:

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
	float m_health;
	float m_maxHealth;

private:
	float roof;
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

	//components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	component::SoundComponent* m_boostSound;
	component::RigidBodyComponent* m_rigidBody;
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