// main.cpp : Defines the entry point for the console application.
//
#include "Thomas.h"
#include "gameobjects\CameraObject.h"
#include "gameobjects\TerrainObject.h"
#include "gameobjects\WaterObject.h"
#include "materials\PhongMaterial.h"
#include "materials\WaterMaterial.h"
#include "materials\TerrainMaterial.h"
#include "scenes\GameScene.h"

#include "gameobjects\TestDirectionalLight.h"
#include "gameobjects\TestPointLight.h"
#include "gameobjects\Ship.h"
#include "graphics\TextRender.h"
#include "graphics\Sprite.h"

#include "postEffects\OceanPostProcess.h"	

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 1920, 1080, L"Plunder Planets");

	//Init wavebank
	thomas::Sound::LoadWaveBank("../res/sounds/soundlib.xwb");

	Scene* gameScene = Scene::AddScene(new GameScene());
	Scene::Init();

	//start
	thomas::ThomasCore::Start();

	return (int)msg.wParam;
}