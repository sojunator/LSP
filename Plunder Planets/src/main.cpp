
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

#include "gameobjects\TestDirectionalLight.h"
#include "gameobjects\TestPointLight.h"
#include "gameobjects\Ship.h"
#include "graphics\TextRender.h"
#include "graphics\Sprite.h"


#include "postEffects\testEffect.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 800, 600, L"Plunder plantits");
	//init code

	//Init shaders
	thomas::graphics::Shader* shader = thomas::graphics::Shader::CreateShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/phong.hlsl");


	 thomas::graphics::Shader::CreateShader("oceanShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		 "../res/shaders/oceanShader.hlsl");

	 thomas::graphics::Shader::CreateShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD,
		 "../res/shaders/skyboxShader.hlsl");


	thomas::graphics::Shader::CreateShader("Terrain", thomas::graphics::Shader::InputLayouts::STANDARD,
		"../res/shaders/Terrain.hlsl");


	//PostFX test shader
	thomas::graphics::Shader::CreateShader("PostFXTest", thomas::graphics::Shader::InputLayouts::POST_EFFECT,
		"../res/shaders/postFXTest.hlsl");

	thomas::graphics::PostEffect::RegisterNewPostEffectType("testFX", new TestEffect("PostFXTest"));

	//thomas::graphics::PostEffect::CreatePostEffect("test", "testFX");

	//Init materials
	thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new PhongMaterial("Phong"));

	thomas::graphics::Material::RegisterNewMaterialType("waterMaterial", new WaterMaterial("oceanShader"));

	thomas::graphics::Material::RegisterNewMaterialType("terrainMaterial", new TerrainMaterial("Terrain"));

	//Init models

	thomas::utils::AssimpLoader::LoadModel("testModel", "../res/models/Ship/ship.fbx", "phongMaterial");
	Material* m = Material::CreateMaterial("terrainMat", "terrainMaterial");

	//utils::Plane::PlaneData plane = utils::Plane::CreatePlane(128, 1);

	thomas::Islands islands(3, m, 1024/4, 0.125, 1024, 20);
	Model * model = Model::CreateModel("Plane-1", islands.GetIsland(0));
	Model * model1 = Model::CreateModel("Plane-2", islands.GetIsland(1));
	Model * model2 = Model::CreateModel("Plane-3", islands.GetIsland(2));




	//Init wavebank
	thomas::Sound::LoadWaveBank("../res/sounds/soundlib.xwb");

	//Init 2D-images for GUI
	thomas::graphics::Sprite::LoadTexture("../res/GUI/cat.png");

	//Init text
	thomas::graphics::TextRender::LoadFont("Gold", "../res/font/myfile.spritefont");


	//Init gameObjects

	//TestObject* t = new TestObject();
	
	new TerrainObject();
	TestDirectionalLight* dirLight = new TestDirectionalLight();
	//TestPointLight* pointLight = new TestPointLight();
	CameraObject* c = new CameraObject();
	Ship* ship = new Ship();
	new WaterObject();



	//start
	thomas::ThomasCore::Start();
	delete c;

	return (int)msg.wParam;
}

