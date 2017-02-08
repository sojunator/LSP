// main.cpp : Defines the entry point for the console application.
//
#include "Thomas.h"
#include "gameobjects\CameraObject.h"
#include "gameobjects\TerrainObject.h"
#include "gameobjects\WaterObject.h"
#include "materials\PhongMaterial.h"
#include "materials\WaterMaterial.h"
#include "materials\TerrainMaterial.h"

#include "gameobjects\TestDirectionalLight.h"
#include "gameobjects\TestPointLight.h"
#include "gameobjects\Ship.h"


#include "postEffects\OceanPostProcess.h"	

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 1920, 1080, L"Plunder plantits");
	//init code
	double time = thomas::Time::GetInitTime();
	srand(time);



	//Init shaders
	thomas::graphics::Shader* shader = thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/phong.hlsl");


	 thomas::graphics::Shader::CreateShader("oceanShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		 "../res/shaders/oceanShader.hlsl");

	 thomas::graphics::Shader::CreateShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		 "../res/shaders/skyboxShader.hlsl");


	thomas::graphics::Shader::CreateShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/Terrain.hlsl");


	//PostFX test shader
	thomas::graphics::Shader::CreateShader("OceanFX", thomas::graphics::Shader::InputLayouts::POST_EFFECT,
		"../res/shaders/oceanPostProcess.hlsl");

//	thomas::graphics::PostEffect::RegisterNewPostEffectType("oceanEffect", new OceanPostProcess("OceanFX"));

//	thomas::graphics::PostEffect::CreatePostEffect("test", "oceanEffect");

	//Init materials
	thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong"));

	thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("oceanShader"));

	thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain"));

	//Init models
	thomas::utils::AssimpLoader::LoadModel("box", "../res/models/box.obj", "phongMaterial");
	thomas::utils::AssimpLoader::LoadModel("cannonball", "../res/models/cannonball/cannonball.obj", "phongMaterial");
	thomas::utils::AssimpLoader::LoadModel("testModel0", "../res/models/Boat/ship.obj", "phongMaterial");
	thomas::utils::AssimpLoader::LoadModel("testModel1", "../res/models/Boat/ship1.obj", "phongMaterial");
	thomas::utils::AssimpLoader::LoadModel("testModel2", "../res/models/Boat/ship2.obj", "phongMaterial");
	//thomas::utils::AssimpLoader::LoadModel("testModel0", "../res/models/Boat/ship0.obj", "phongMaterial");

	Material* m = Material::CreateMaterial("terrainMat", "terrainMaterial");
	thomas::Islands* islands = new thomas::Islands(10, m, 1024 / 8, 0.125, 1024 / 4, 30);
	Model * model = Model::CreateModel("Plane-1", islands->GetIsland(0));




	//Init wavebank
	thomas::Sound::LoadWaveBank("../res/sounds/soundlib.xwb");


	//Init gameObjects

	
	thomas::object::GameObject::Instantiate(new TerrainObject());
	thomas::object::GameObject::Instantiate(new TestDirectionalLight());
	//TestPointLight* pointLight = new TestPointLight();
	thomas::object::GameObject::Instantiate(new CameraObject());
	thomas::object::GameObject::Instantiate(new Ship());
	thomas::object::GameObject::Instantiate(new WaterObject());

	//start
	thomas::ThomasCore::Start();

	return (int)msg.wParam;
}