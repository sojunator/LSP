
// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"
#include "gameobjects\TestObject.h"
#include "gameobjects\CameraObject.h"
#include "gameobjects\TerrainObject.h"
#include "gameobjects\WaterObject.h"
#include "materials\PhongMaterial.h"
#include "materials\WaterMaterial.h"
#include "materials\TerrainMaterial.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600, L"Plunder plantits");
	//init code

	//Init shaders
	 thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/phong.hlsl");

	 thomas::graphics::Shader::CreateShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		 "../res/shaders/skyboxShader.hlsl");

	thomas::graphics::Shader::CreateShader("tesselationShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/tesselationTest.hlsl");


	thomas::graphics::Shader::CreateShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/Terrain.hlsl");


	//Init materials
	thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong"));

	thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("tesselationShader"));

	thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain"));

	//Init models

	thomas::utils::AssimpLoader::LoadModel("testModel", "../res/models/vase/vase.obj", "phongMaterial");
	Material* m = Material::CreateMaterial("terrainMat", "terrainMaterial");
	thomas::graphics::Model::CreateModel("Plane-1", thomas::utils::Plane::CreatePlane(256, 1, "Plane-1", m));


	//Init gameObjects

	TestObject* t = new TestObject();
	CameraObject* c = new CameraObject();
	new WaterObject();



	//start
	thomas::ThomasCore::Start();
	delete c;

	return (int)msg.wParam;
}

