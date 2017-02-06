#pragma once
#include "../src/Scene.h"
#include "../gameobjects/TestObject.h"
#include "../gameobjects/CameraObject.h"
#include "../gameobjects/TerrainObject.h"
#include "../gameobjects/WaterObject.h"
#include "../materials/PhongMaterial.h"
#include "../materials/TerrainMaterial.h"
#include "../materials/WaterMaterial.h"

class GameScene : public thomas::Scene
{
	GameScene() : Scene()
	{
		//Init shaders
		m_shaders.push_back(thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/test.hlsl"));
		m_shaders.push_back(thomas::graphics::Shader::CreateShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/skyboxShader.hlsl"));
		m_shaders.push_back(thomas::graphics::Shader::CreateShader("tesselationShader", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/tesselationTest.hlsl"));
		m_shaders.push_back(thomas::graphics::Shader::CreateShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD,
			"../res/shaders/Terrain.hlsl"));

		//Init materials
		m_materials.push_back(thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong")));
		m_materials.push_back(thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("tesselationShader")));
		m_materials.push_back(thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain")));

		//Init models
		m_models.push_back(thomas::utils::AssimpLoader::LoadModel("testModel", "../res/models/Ubot/Ubot.obj", "phongMaterial"));
		Material* m = Material::CreateMaterial("terrainMat", "terrainMaterial"); //push_back här eller under init? Fattar inte användning av material.
		m_models.push_back(thomas::graphics::Model::CreateModel("Plane-1", thomas::utils::Plane::CreatePlane(256, 1, "Plane-1", m)));

		//Init gameObjects
		m_objects.push_back(new TestObject());
		m_objects.push_back(new CameraObject());
		m_objects.push_back(new WaterObject());
	};
};