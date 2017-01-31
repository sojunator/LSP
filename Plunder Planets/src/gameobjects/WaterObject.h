#pragma once
#include "Thomas.h"
#include "../materials/WaterMaterial.h"
using namespace thomas;
using namespace object;
class WaterObject : public GameObject
{
private:
public:
	WaterObject() : GameObject("WaterObject")
	{
		m_waterMaterial = (Material::createMaterial("waterMat", "waterMaterial"));
		Model::CreateModel("waterModel", utils::Plane::CreatePlane(256, 0.015625, "waterPlane", m_waterMaterial));

		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("waterModel");

	};

	bool Start()
	{
		return true;
	}

	void Update()
	{
		m_waterMaterial->Update();
	}



private:
	component::RenderComponent* m_renderer;
	Material* m_waterMaterial;
};