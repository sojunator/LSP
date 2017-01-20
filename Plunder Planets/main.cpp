
// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"

#include <string>
#include <iostream>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 600, 800);
	//init code
	//Assimp::Importer importer;
	//Assimp::BaseImporter importer2;
	//importer2 = importer.GetImporter(size_t(0));
	//start
	thomas::ThomasCore::Start();

	return (int)msg.wParam;
}

