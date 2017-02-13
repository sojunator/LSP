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
		oceanSim = ((WaterMaterial*)m_waterMaterial)->GetOceanSim();
		utils::Plane::PlaneData pData = utils::Plane::CreatePlane(dim, 1.0 / 10);
		Mesh* m = new Mesh(pData.verts, pData.indices, "oceanMesh", m_waterMaterial);
		std::vector<Mesh*> meshes;
		meshes.push_back(m);
		Model::CreateModel("ocean", meshes);

		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("ocean");

		//m_transform->SetScale(0.05);
		m_transform->SetPosition(math::Vector3(-dim/2, 0, dim/2));

		m_oceanSounds = AddComponent<component::SoundComponent>();
	}

	void Update()
	{
		delayLeft -= Time::GetDeltaTime();

		if (delayLeft < 0)
		{
			delayLeft = soundEffectDelay;

		}
	}

	bool GetCollisionAt(component::Transform* transform)
	{
		math::Vector3 position = transform->GetPosition();
		float uvScale = 1.0 / 500.0;
		float uvOffset = 0.5f / 512.0f;
		math::Vector2 texCoord;
		position.x -= 1000;
		position.z += 1000;
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
		LOG("x: " << waterPos.x << " y: " << waterPos.y << " z: " << waterPos.z);
		position = transform->GetPosition();
		position.y = waterPos.z;
		transform->SetPosition(position);
		return true;
	}


private:
	float soundEffectDelay = 3;
	float delayLeft = soundEffectDelay;
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_oceanSounds;
	Material* m_waterMaterial;
	utils::ocean::OceanSimulator* oceanSim;
	
};