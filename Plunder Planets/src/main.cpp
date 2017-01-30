
// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"
#include "gameobjects\TestObject.h"
#include "gameobjects\CameraObject.h"
#include "materials\PhongMaterial.h"
#include "materials\WaterMaterial.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600, L"Plunder plantits");
	//init code

	//Init shaders
	thomas::graphics::Shader* shader = thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/phong.hlsl");

	thomas::graphics::Shader::CreateShader("tesselationShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/tesselation/tesselationTestVS.hlsl",
		"",
		"../res/shaders/tesselation/tesselationTestHS.hlsl",
		"../res/shaders/tesselation/tesselationTestDS.hlsl",
		"../res/shaders/tesselation/tesselationTestPS.hlsl");

	//Init materials
	thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong"));

	thomas::graphics::Material::RegisterNewMaterialType("tessMaterial", new WaterMaterial("tesselationShader"));

	//Init models

	thomas::utils::AssimpLoader::LoadModel("testModel", "../res/models/Ubot/Ubot.obj", "tessMaterial");


	//Init gameObjects

	TestObject* t = new TestObject();
	CameraObject* c = new CameraObject();



	//start
	thomas::ThomasCore::Start();
	return (int)msg.wParam;
}

