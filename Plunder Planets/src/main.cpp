
// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"
#include "gameobjects\TestObject.h"
#include "gameobjects\CameraObject.h"
#include "gameobjects\TerrainObject.h"

#include "materials\PhongMaterial.h"
#include "materials\WaterMaterial.h"
#include "materials\TerrainMaterial.h"

#include <time.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	srand(8);

	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600, L"Plunder plantits");
	//init code

	//Init shaders
	thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/phong.hlsl");

	thomas::graphics::Shader::CreateShader("tesselationShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/tesselationTest.hlsl");


	thomas::graphics::Shader::CreateShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/Terrain.hlsl");


	//Init materials
	thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong"));

	thomas::graphics::Material::RegisterNewMaterialType("tessMaterial", new WaterMaterial("tesselationShader"));

	thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain"));

	//Init models
	thomas::utils::AssimpLoader::LoadModel("testModel", "../res/models/Ubot/Ubot.obj", "phongMaterial");
	Material* m = Material::CreateMaterial("terrainMat", "terrainMaterial");
	thomas::Islands* islands = new thomas::Islands(10, m, 1024 / 4, 0.125, 1024/2, 100);

	Model * model = Model::CreateModel("Plane-1", islands->GetIsland(0));




	//Init gameObjects
	TestObject* t = new TestObject();
	TerrainObject* terrainMap = new TerrainObject();
	CameraObject* c = new CameraObject();



	//start
	thomas::ThomasCore::Start();
	delete terrainMap;
	delete c;

	return (int)msg.wParam;
}

