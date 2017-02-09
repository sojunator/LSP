#pragma once
#include "Thomas.h"
#include "Projectile.h"

using namespace thomas;
using namespace object;
class OceanFloor : public GameObject
{

private:

public:
	OceanFloor() : GameObject("OceanFloor")
	{

	}

	void Start()
	{
		m_oceanFloor = AddComponent<component::RenderComponent>();
		utils::Plane::PlaneData pData = utils::Plane::CreatePlane(2000, 1.0 / 100);
		thomas::graphics::Material* mat = thomas::graphics::Material::CreateMaterial("oceanFloorMat", "terrainMaterial");

		thomas::graphics::Mesh* m = new thomas::graphics::Mesh(pData.verts, pData.indices, "oceanFloor", mat);
		std::vector<thomas::graphics::Mesh*> meshes;
		meshes.push_back(m);
		thomas::graphics::Model::CreateModel("oceanFloor", meshes);

		m_oceanFloor->SetModel("oceanFloor");
		m_transform->SetPosition(-1000, -10, 1000);
	}

private:
	component::RenderComponent* m_oceanFloor;
};