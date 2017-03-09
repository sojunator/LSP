#pragma once
#include "Thomas.h"
#include "EditorGameObject.h"
#include "CameraObject.h"
#include "TempMaterial.h"
#include "ShipObject.h"
#include "Plane.h"

class ParticleEditorScene : public thomas::Scene
{
public:
	ParticleEditorScene() : Scene("ParticleEditorScene")
	{
		LoadShader("particleShader", thomas::graphics::Shader::InputLayouts::NONE, "../res/shaders/particleShader.hlsl");
		LoadShader("Phong", thomas::graphics::Shader::InputLayouts::STANDARD, "../res/shaders/phong.hlsl");
		thomas::graphics::Material::RegisterNewMaterialType("phongMaterial", new TempMaterial("Phong"));
		LoadMaterial("phongMaterial", new TempMaterial("Phong"));

		LoadModel("plane", "../res/models/plane.obj", "phongMaterial");
		LoadModel("ship", "../res/models/Boat/ship0fbx.fbx", "phongMaterial");

		LoadObject<CameraObject>();
		LoadObject<Plane>();
		LoadObject<EditorGameObject>();
		ShipObject* ship = LoadObject<ShipObject>();

		thomas::utils::DebugTools::CreateBar("menuBar");

		TwAddButton(thomas::utils::DebugTools::GetBar("menuBar")->bar, "Toggle Ship", Helper::ToggleModel, ship, "label='Toggle Ship (Rotate with arrow keys)'");
		TwAddButton(thomas::utils::DebugTools::GetBar("menuBar")->bar, "Add system", Helper::AddSystem, this, "label='Add particle emitter'");

	}
};