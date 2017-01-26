
// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"
#include "gameobjects\TestObject.h"
#include "gameobjects\CameraObject.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600, L"Plunder plantits");
	//init code



	thomas::graphics::Shader* shader = thomas::graphics::Shader::CreateShader("Phong", "../res/shaders/phong.hlsl", thomas::graphics::Shader::InputLayouts::STANDARD);
	shader->Bind();
	thomas::utils::AssimpLoader::LoadModel("testModel", "../res/models/armchair.obj");

	new TestObject();
	CameraObject* c = new CameraObject();

	//start
	thomas::ThomasCore::Start();
	return (int)msg.wParam;
}

