
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

	thomas::utils::AssimpLoader::LoadModel("sphere", "../res/models/sphere1.obj");

	new TestObject();
	CameraObject* c = new CameraObject();

	//start
	thomas::ThomasCore::Start();
	return (int)msg.wParam;
}

