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

class GameScene : public thomas::Scene
{
public:
	GameScene() : Scene()
	{
		//Init shaders
		m_shaders.push_back(thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/test.hlsl"));
		m_shaders.push_back(thomas::graphics::Shader::CreateShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/skyboxShader.hlsl"));
		/*m_shaders.push_back(thomas::graphics::Shader::CreateShader("tesselationShader", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/tesselationTest.hlsl"));*/
		m_shaders.push_back(thomas::graphics::Shader::CreateShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/Terrain.hlsl"));
		thomas::graphics::Shader::CreateShader("oceanShader", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/oceanShader.hlsl");
		thomas::graphics::Shader::CreateShader("OceanFX", thomas::graphics::Shader::InputLayouts::POST_EFFECT,
			"../res/shaders/oceanPostProcess.hlsl");

		//Init materials
		//m_materials.push_back(thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong")));
		//m_materials.push_back(thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("tesselationShader")));
		thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("oceanShader"));
		//m_materials.push_back(thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain")));

		//Init models
		//m_models.push_back(thomas::utils::AssimpLoader::LoadModel("testModel", "../res/models/Ubot/Ubot.obj", "phongMaterial"));
		thomas::utils::AssimpLoader::LoadModel("testModel0", "../res/models/Boat/ship.obj", "phongMaterial");
		thomas::utils::AssimpLoader::LoadModel("testModel1", "../res/models/Boat/ship1.obj", "phongMaterial");
		thomas::utils::AssimpLoader::LoadModel("testModel2", "../res/models/Boat/ship2.obj", "phongMaterial");
		//Material* m = Material::CreateMaterial("terrainMat", "terrainMaterial");
		//m_models.push_back(thomas::graphics::Model::CreateModel("Plane-1", thomas::utils::Plane::CreatePlane(256, 1, "Plane-1", m)));
		//thomas::Islands* islands = new thomas::Islands(10, m, 1024 / 8, 0.125, 1024 / 4, 30);
		//Model * model = Model::CreateModel("Plane-1", islands->GetIsland(0));

		/*m_gameObjects.push_back(new TestObject());
		m_gameObjects.push_back(new CameraObject());
		m_gameObjects.push_back(new WaterObject());*/
		//Init gameObjects
		m_gameObjects.push_back(new TerrainObject());
		m_gameObjects.push_back(new TestDirectionalLight());

		//Init + instantiate objects, instantiate gameObjects
		for (GameObject* object : m_gameObjects)
			Object::Instantiate(object);

		//Init Cameras
		std::vector<GameObject*> cameraObjects = this->GetObjectsByComponent<object::component::Camera>();
		for(GameObject* object : cameraObjects)
			m_cameras.push_back(object->GetComponent<object::component::Camera>());
	};
};