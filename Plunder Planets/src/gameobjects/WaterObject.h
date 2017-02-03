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
		int dim = 8000;

		m_waterMaterial = (Material::CreateMaterial("waterMat", "waterMaterial"));
		Model::CreateModel("waterModel", utils::Plane::CreatePlane(dim, 1.0/16, "waterPlane", m_waterMaterial));

		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("waterModel");

		
		//m_transform->SetScale(0.05);
		m_transform->SetPosition(math::Vector3(-dim / 2, 0, dim / 2));
		
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