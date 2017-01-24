
// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	MSG msg = { 0 };
	thomas::utils::Model model;
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600, L"Plunder plantets");
	//init code
	model = thomas::utils::AssimpLoader::LoadModel("objects/sphere1.obj");

	thomas::graphics::shader::Shader("testShader", "../shaders/test.hlsl");


	//start
	thomas::ThomasCore::Start();
	return (int)msg.wParam;
}

