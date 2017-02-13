#pragma once
#include "../src/Scene.h"
#include "../../THOMAS/src/object/Object.h"
#include "../gameobjects/CameraObject.h"
#include "../gameobjects/TerrainObject.h"
#include "../gameobjects/WaterObject.h"
#include "../gameobjects/TestDirectionalLight.h"
#include "../materials/PhongMaterial.h"
#include "../materials/TerrainMaterial.h"
#include "../materials/WaterMaterial.h"
#include "../src/graphics/Sprite.h"
#include "../src/graphics/TextRender.h"

class GameScene : public thomas::Scene
{
public:
	GameScene() : Scene("GameScene")
	{
		//Init shaders
		/*thomas::graphics::Shader* shader = thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/phong.hlsl");
		thomas::graphics::Shader::CreateShader("oceanShader", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/oceanShader.hlsl");
		thomas::graphics::Shader::CreateShader("OceanFX", thomas::graphics::Shader::InputLayouts::POST_EFFECT,
			"../res/shaders/oceanPostProcess.hlsl");
		thomas::graphics::Shader::CreateShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/skyboxShader.hlsl");
		thomas::graphics::Shader::CreateShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/Terrain.hlsl");*/
		LoadShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/phong.hlsl");
		LoadShader("oceanShader", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/oceanShader.hlsl");
		LoadShader("OceanFX", thomas::graphics::Shader::InputLayouts::POST_EFFECT, "../res/shaders/oceanPostProcess.hlsl");
		LoadShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/skyboxShader.hlsl");
		LoadShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/Terrain.hlsl");

		//Init materials
		/*thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong"));
		thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("oceanShader"));
		thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain"));*/
		LoadMaterial("phongMaterial", new PhongMaterial("Phong"));
		LoadMaterial("waterMaterial", new WaterMaterial("oceanShader"));
		LoadMaterial("terrainMaterial", new TerrainMaterial("Terrain"));
		
		//Init models
		LoadModel("cannonball", "../res/models/cannonball/cannonball.obj", "phongMaterial");
		LoadModel("testModel0", "../res/models/Boat/ship0.obj", "phongMaterial");
		LoadModel("testModel1", "../res/models/Boat/ship.obj", "phongMaterial");
		LoadModel("testModel2", "../res/models/Boat/ship1.obj", "phongMaterial");
		LoadModel("testModel3", "../res/models/Boat/ship2.obj", "phongMaterial");

		//Init 2D-images for GUI
		if (Window::GetAspectRatio() == Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/button_plunder.png");

		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_1610)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/1610tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/button_plunder.png");
		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_43)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/43tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/button_plunder.png");
		}		
		else
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/button_plunder.png");
		}

		//Init text
		thomas::graphics::TextRender::LoadFont("Name", "../res/font/pirate.spritefont");
		thomas::graphics::TextRender::LoadFont("Gold", "../res/font/myfile.spritefont");

		//Init objects lägga till LoadObjects i scene?
		m_cameraObject = thomas::object::GameObject::Instantiate<CameraObject>(this);
		m_terrainObject = thomas::object::GameObject::Instantiate<TerrainObject>(this);
		m_ship = thomas::object::GameObject::Instantiate<Ship>(this);
		m_waterObject = thomas::object::GameObject::Instantiate<WaterObject>(this);
		m_testDirectionalLight = thomas::object::GameObject::Instantiate<TestDirectionalLight>(this);

		//Init Cameras //lägga i scene init eller loadscene kanske?
		std::vector<object::GameObject*> cameraObjects = object::GameObject::FindGameObjectsWithComponent<object::component::Camera>();
		for(GameObject* object : cameraObjects)
			m_cameras.push_back(object->GetComponent<object::component::Camera>());
	};
	
	void UnloadScene()
	{
		thomas::object::GameObject::Destroy(m_cameraObject);
		thomas::object::GameObject::Destroy(m_terrainObject);
		thomas::object::GameObject::Destroy(m_ship);
		thomas::object::GameObject::Destroy(m_waterObject);
		thomas::object::GameObject::Destroy(m_testDirectionalLight);
	}

private:
	CameraObject* m_cameraObject;
	TerrainObject* m_terrainObject;
	Ship* m_ship;
	WaterObject* m_waterObject;
	TestDirectionalLight* m_testDirectionalLight;
};