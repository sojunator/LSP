// main.cpp : Defines the entry point for the console application.
//

#include "Thomas.h"
#include "gameobjects\CameraObject.h"
#include "gameobjects\WaterObject.h"
#include "materials\PhongMaterial.h"
#include "materials\WaterMaterial.h"
#include "materials\TerrainMaterial.h"

#include "scenes\MenuScene.h"

#include "gameobjects\TestDirectionalLight.h"
#include "gameobjects\TestPointLight.h"
#include "gameobjects\Ship.h"
#include "graphics\TextRender.h"
#include "graphics\Sprite.h"

#include "postEffects\OceanPostProcess.h"	
 
#define _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	MSG msg = { 0 };
	ShowCursor(true);
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 1920, 1080, L"Plunder Planets");

	//Init wavebank
	thomas::Sound::LoadWaveBank("../res/sounds/soundlib.xwb");
	ShipStats::s_playerStats = new ShipStats();
	Scene* menuScene = Scene::LoadScene<MenuScene>();

	//start
	thomas::ThomasCore::Start();
	
	delete ShipStats::s_playerStats;

	_CrtDumpMemoryLeaks();
	return (int)msg.wParam;
}