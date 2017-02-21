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
		m_dimensions = 20000;

		m_waterMaterial = (Material::CreateMaterial("waterMat", "waterMaterial"));
		oceanSim = ((WaterMaterial*)m_waterMaterial)->GetOceanSim();
		utils::Plane::PlaneData pData = utils::Plane::CreatePlane(m_dimensions, 1.0 / 100);
		Mesh* m = new Mesh(pData.verts, pData.indices, "oceanMesh", m_waterMaterial);
		std::vector<Mesh*> meshes;
		meshes.push_back(m);
		Model::CreateModel("ocean", meshes);

		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("ocean");

		m_transform->SetPosition(math::Vector3(-m_dimensions/2, 0, m_dimensions /2));

		m_oceanSounds = AddComponent<component::SoundComponent>();

		//m_rb = AddComponent<component::RigidBodyComponent>();
		//m_rb->SetCollider(new btStaticPlaneShape(btVector3(0,1,0),1));

	}

	void Update()
	{
		delayLeft -= Time::GetDeltaTime();

		if (delayLeft < 0)
		{
			delayLeft = soundEffectDelay;

		}

	}

	void SetOceanCenter(float x, float z)
	{
		float gridSize = 100.0;

		x = x / gridSize;
		x = floor(x);
		x *= gridSize;
		z = z / gridSize;
		z = floor(z);
		z *= gridSize;
		m_transform->SetPosition(math::Vector3(x-m_dimensions / 2, 0, z+m_dimensions / 2));
	}



	math::Vector3 GetCollisionAt(component::Transform* transform)
	{
		math::Vector3 position = transform->GetPosition();
		float uvScale = 1.0 /oceanSim->getParameters().patch_length;
		float uvOffset = 0.5f / oceanSim->getParameters().dmap_dim;
		math::Vector2 texCoord;
		position.x -= m_dimensions/2;
		position.z += m_dimensions/2;
		texCoord.x = position.x * uvScale + uvOffset;

		if (texCoord.x < 0)
		{
			texCoord.x = 1.0 - std::fmod(abs(texCoord.x), 1.0);
		}
		else
		{
			texCoord.x = std::fmod(texCoord.x, 1.0);
		}

		texCoord.y = position.z * uvScale + uvOffset;

		if (texCoord.y < 0)
		{
			texCoord.y = 1.0 - std::fmod(abs(texCoord.y), 1.0);
		}
		else
		{
			texCoord.y = std::fmod(texCoord.y, 1.0);
		}

		math::Vector3 waterPos = oceanSim->GetPositionAtCoord(texCoord);
		position = transform->GetPosition();
		
		waterPos = math::Vector3(waterPos.x, waterPos.y, waterPos.z);
		return waterPos;

	}


private:
	int m_dimensions;
	float soundEffectDelay = 3;
	float delayLeft = soundEffectDelay;
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_oceanSounds;
	Material* m_waterMaterial;
	utils::ocean::OceanSimulator* oceanSim;
	component::RigidBodyComponent* m_rb;

	float waterX;
	
};