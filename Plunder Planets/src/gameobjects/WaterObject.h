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
		m_waterMaterial = (Material::CreateMaterial("waterMat", "waterMaterial"));
		Model::CreateModel("waterModel", utils::Plane::CreatePlane(512*16, 1.0/64.0, "waterPlane", m_waterMaterial));

		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("waterModel");


		
	};

	bool Start()
	{
		return true;
	}

	void Update()
	{
	}



private:
	component::RenderComponent* m_renderer;
	Material* m_waterMaterial;
	
};