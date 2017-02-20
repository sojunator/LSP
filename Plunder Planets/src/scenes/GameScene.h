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
#include "../gameobjects/PhysicsObject.h"
#include "../gameobjects/StandardParticleEmitter.h"
#include "../src/graphics/ParticleSystem.h"


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

		

		//Init 2D-images for GUI
		if (Window::GetAspectRatio() == Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/le.png");

		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_1610)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/1610tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/le.png");
		}
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_43)
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/43tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/le.png");
		}		
		else
		{
			thomas::graphics::Sprite::LoadTexture("GUI", "../res/GUI/169tex.png");
			thomas::graphics::Sprite::LoadTexture("Button", "../res/GUI/le.png");
		}

		//Init text
		thomas::graphics::TextRender::LoadFont("Name", "../res/font/pirate.spritefont");
		thomas::graphics::TextRender::LoadFont("Gold", "../res/font/myfile.spritefont");

		LoadObject<CameraObject>();
		LoadObject<TerrainObject>();
		LoadObject<Ship>();
		LoadObject<WaterObject>();
		LoadObject<TestDirectionalLight>();
		LoadObject<StandardParticleEmitter>();
		//LoadObject<PhysicsObject>();

		
	};
	
	/*void UnloadScene()
	{
		thomas::object::GameObject::Destroy(m_cameraObject);
		thomas::object::GameObject::Destroy(m_terrainObject);
		thomas::object::GameObject::Destroy(m_ship);
		thomas::object::GameObject::Destroy(m_waterObject);
		thomas::object::GameObject::Destroy(m_testDirectionalLight);
	}*/

private:

};