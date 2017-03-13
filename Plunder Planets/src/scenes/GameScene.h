#pragma once
#include "../src/Scene.h"
#include "../../THOMAS/src/object/Object.h"
#include "../gameobjects/CameraObject.h"
#include "../gameobjects/Terrain/IslandManager.h"
#include "../gameobjects/WaterObject.h"
#include "../gameobjects/TestDirectionalLight.h"
#include "../gameobjects/OceanFloor.h"
#include "../materials/PhongMaterial.h"
#include "../materials/TerrainMaterial.h"
#include "../materials/WaterMaterial.h"
#include "../src/graphics/Sprite.h"
#include "../src/graphics/TextRender.h"
#include "../gameobjects/PhysicsObject.h"
#include "../gameobjects/StandardParticleEmitter.h"
#include "../gameobjects/Ship.h"
#include "../gameobjects/Wormhole.h"
#include "../gameobjects/PauseObjectMenuObject.h"
#include "../gameobjects/SettingsMenuObject.h"
#include "../gameobjects/EnemyManager.h"
#include "../gameobjects/MainGameManager.h"
#include "../gameobjects/HealthCrate.h"

class GameScene : public thomas::Scene
{
public:
	GameScene() : Scene("GameScene")
	{
		//Init shaders
		ShipStats::s_currentLevel += 1;

		LoadShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/phong.hlsl");
		LoadShader("oceanShader", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/oceanShader.hlsl");
		LoadShader("OceanFX", thomas::graphics::Shader::InputLayouts::POST_EFFECT, "../res/shaders/oceanPostProcess.hlsl");
		LoadShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/skyboxShader.hlsl");
		LoadShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/Terrain.hlsl");
		LoadShader("particleShader", thomas::graphics::Shader::InputLayouts::NONE, "../res/shaders/particleShader.hlsl");

		//Init materials
		LoadMaterial("phongMaterial", new PhongMaterial("Phong"));
		LoadMaterial("waterMaterial", new WaterMaterial("oceanShader"));
		LoadMaterial("terrainMaterial", new TerrainMaterial("Terrain"));
		
		//Init models		
		LoadModel("cannonball", "../res/models/cannonball/cannonball.fbx", "phongMaterial");
		LoadModel("playerModel", "../res/models/Boat/ship0fbx.fbx", "phongMaterial");
		LoadModel("basicEnemy", "../res/models/Boat/shipenemy.fbx", "phongMaterial");
		LoadModel("tobyEnemy1", "../res/models/Boat/tobyboatRed.fbx", "phongMaterial");
		LoadModel("tobyEnemy0", "../res/models/Boat/tobyboat.fbx", "phongMaterial");
		LoadModel("box1", "../res/models/box.obj", "phongMaterial");
		LoadModel("healthCrate", "../res/models/crate_mesh.obj", "phongMaterial");

		

		//Init 2D-images for GUI
		if (Window::GetAspectRatio() == Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
			thomas::graphics::Sprite::LoadTexture("Goldbar", "../res/GUI/goldbar.png");
			thomas::graphics::Sprite::LoadTexture("GoldbarEmpty", "../res/GUI/goldbar-empty.png");
			thomas::graphics::Sprite::LoadTexture("Wormhole open", "../res/GUI/Wormhole open.png");
			thomas::graphics::Sprite::LoadTexture("Plunder Planets", "../res/GUI/Plunder Planets.png");
		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_1610)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/1610tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
			thomas::graphics::Sprite::LoadTexture("Goldbar", "../res/GUI/goldbar.png");
			thomas::graphics::Sprite::LoadTexture("GoldbarEmpty", "../res/GUI/goldbar-empty.png");
		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_43)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/43tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
			thomas::graphics::Sprite::LoadTexture("Goldbar", "../res/GUI/goldbar.png");
			thomas::graphics::Sprite::LoadTexture("GoldbarEmpty", "../res/GUI/goldbar-empty.png");
		}		
		else
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
			thomas::graphics::Sprite::LoadTexture("Goldbar", "../res/GUI/goldbar.png");
			thomas::graphics::Sprite::LoadTexture("GoldbarEmpty", "../res/GUI/goldbar-empty.png");
		}

		//Init text
		thomas::graphics::TextRender::LoadFont("Pirate", "../res/font/pirate.spritefont");

		m_cameraObject = LoadObject<CameraObject>();
		m_waterObject = LoadObject<WaterObject>();

		//Not a GameObject
		s_islandManager = new IslandManager(this);
		
		m_testDirectionalLight = LoadObject<TestDirectionalLight>();
		LoadObject<OceanFloor>();
		LoadObject<PauseObjectMenuObject>();
		LoadObject<Wormhole>(math::Vector3(0,100,0),math::Quaternion::Identity);
		LoadObject<SettingsMenuObject>();
		LoadObject<EnemyManager>();
		LoadObject<MainGameManager>();
		LoadObject<HealthCrate>();
		
		//LoadObject<PhysicsObject>();
		
	};
	
	~GameScene()
	{
		delete s_islandManager;
	}

public:
	static IslandManager* s_islandManager;

private:
	CameraObject* m_cameraObject;
	Ship* m_ship;
	//std::vector<Enemy*> m_enemyShip;
	WaterObject* m_waterObject;
	TestDirectionalLight* m_testDirectionalLight;
	float test = 0.0f;
};