#pragma once
#include "Thomas.h"
#include "../gameobjects/CameraObject.h"
#include "../materials/PhongMaterial.h"
#include "../gameobjects/testGameObject.h"
#include "../gameobjects/TestDirectionalLight.h"
#define THOMAS_SHOW_ALL_ERRORS 1
class RenderingTestScene : public thomas::Scene
{
public:
	RenderingTestScene() : Scene("RenderingTestScene")
	{
		LoadShader("skyboxShader", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/skyboxShader.hlsl");
		LoadShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/phong.hlsl");
		LoadMaterial("phongMaterial", new PhongMaterial("Phong"));
		LoadModel("sponza", "../res/models/sponza/sponza.obj", "phongMaterial"); //Not on git. URL: https://drive.google.com/open?id=0BzhuxwC12bJJeGJoTkVsMDZLaUk

		 LoadObject<CameraObject>();
		 LoadObject<TestGameObject>();
		 LoadObject<TestDirectionalLight>();
	};
};