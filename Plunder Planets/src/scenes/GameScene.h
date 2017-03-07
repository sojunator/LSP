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
#include "../gameobjects/Enemy.h"
#include "../gameobjects/Ship.h"
#include "../gameobjects/Wormhole.h"

class GameScene : public thomas::Scene
{
public:
	GameScene() : Scene("GameScene")
	{
		//Init shaders

		LoadShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/phong.hlsl");
		LoadShader("oceanShader", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/oceanShader.hlsl");
		LoadShader("OceanFX", thomas::graphics::Shader::InputLayouts::POST_EFFECT, "../res/shaders/oceanPostProcess.hlsl");
		LoadShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/skyboxShader.hlsl");
		LoadShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/Terrain.hlsl");
		LoadShader("particleShader", thomas::graphics::Shader::InputLayouts::NONE, "../res/shaders/particleShader.hlsl");

		//Init materials
		thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong"));
		thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("oceanShader"));
		thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain"));
		LoadMaterial("phongMaterial", new PhongMaterial("Phong"));
		LoadMaterial("waterMaterial", new WaterMaterial("oceanShader"));
		LoadMaterial("terrainMaterial", new TerrainMaterial("Terrain"));
		
		//Init models
		LoadModel("cannonball", "../res/models/cannonball/cannonball.fbx", "phongMaterial");
		LoadModel("testModel0", "../res/models/Boat/ship0fbx.fbx", "phongMaterial");
		LoadModel("testModel1", "../res/models/Boat/ship1fbx.fbx", "phongMaterial");
		LoadModel("testModel2", "../res/models/Boat/ship2fbx.fbx", "phongMaterial");
		LoadModel("testModel3", "../res/models/Boat/ship3fbx.fbx", "phongMaterial");
		LoadModel("testModelEnemy", "../res/models/Boat/shipenemy.fbx", "phongMaterial");
		LoadModel("box1", "../res/models/box.obj", "phongMaterial");

		

		//Init 2D-images for GUI
		if (Window::GetAspectRatio() == Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_1610)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/1610tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_43)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/43tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
		}		
		else
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Health", "../res/GUI/health.png");
			thomas::graphics::Sprite::LoadTexture("BackHealth", "../res/GUI/back.png");
			thomas::graphics::Sprite::LoadTexture("HealthIcon", "../res/GUI/healthSign.png");
			thomas::graphics::Sprite::LoadTexture("ArmorIcon", "../res/GUI/armsign.png");
			thomas::graphics::Sprite::LoadTexture("Armor", "../res/GUI/armor.png");
		}

		//Init text
		thomas::graphics::TextRender::LoadFont("Name", "../res/font/pirate.spritefont");
		thomas::graphics::TextRender::LoadFont("Gold", "../res/font/myfile.spritefont");

		m_cameraObject = LoadObject<CameraObject>();
		m_islandManager = LoadObject<IslandManager>();
		m_waterObject = LoadObject<WaterObject>();
		for (int startEnemies = 0; startEnemies < 1; startEnemies++) //10 = number of AI
		{
			//LoadObject<Enemy>(math::Vector3(startEnemies * 200, 0.5, 200), math::Quaternion::Identity);
		}
		m_testDirectionalLight = LoadObject<TestDirectionalLight>();
		LoadObject<OceanFloor>();
		LoadObject<Wormhole>(math::Vector3(0,100,0),math::Quaternion::Identity);
		//LoadObject<PhysicsObject>();

	};
	

private:
	CameraObject* m_cameraObject;
	IslandManager* m_islandManager;
	IslandObject* m_islandObject;
	Ship* m_ship;
	//std::vector<Enemy*> m_enemyShip;
	WaterObject* m_waterObject;
	TestDirectionalLight* m_testDirectionalLight;
	float test = 0.0f;
};