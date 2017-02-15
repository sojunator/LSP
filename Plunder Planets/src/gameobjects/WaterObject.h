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


	};

	void Start()
	{
		int dim = 2000;

		m_waterMaterial = (Material::CreateMaterial("waterMat", "waterMaterial"));

		utils::Plane::PlaneData pData = utils::Plane::CreatePlane(dim, 1.0 / 10);
		Mesh* m = new Mesh(pData.verts, pData.indices, "oceanMesh", m_waterMaterial);
		std::vector<Mesh*> meshes;
		meshes.push_back(m);
		Model::CreateModel("ocean", meshes);

		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("ocean");

		//m_transform->SetScale(0.05);
		m_transform->SetPosition(math::Vector3(-dim / 2, 0, dim / 2));

		m_oceanSounds = AddComponent<component::SoundComponent>();

		m_rb = AddComponent<component::RigidBodyComponent>();
		m_rb->SetCollider(new btStaticPlaneShape(btVector3(0,1,0),1));
		m_rb->SetMass(0);
		m_rb->SetKinematic(true);

	}

	void Update()
	{
		delayLeft -= Time::GetDeltaTime();

		if (delayLeft < 0)
		{
			delayLeft = soundEffectDelay;

		}
	}



private:
	float soundEffectDelay = 3;
	float delayLeft = soundEffectDelay;
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_oceanSounds;
	Material* m_waterMaterial;

	component::RigidBodyComponent* m_rb;
	
};