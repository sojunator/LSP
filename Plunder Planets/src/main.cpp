
// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"
#include "gameobjects\TestObject.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	MSG msg = { 0 };
	thomas::utils::Model model;
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600, L"Plunder plantits");
	//init code

	thomas::utils::AssimpLoader::LoadModel("../res/models/box.obj");

	new TestObject();
	//CameraObject* c = new CameraObject();

	//start
	thomas::ThomasCore::Start();
	return (int)msg.wParam;
}

