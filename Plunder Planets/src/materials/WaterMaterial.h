#pragma once
#include "Thomas.h"
#include "utils/Ocean/OceanSimulator.h"
using namespace thomas;
using namespace graphics;

class WaterMaterial : public Material
{
private:
	Material* CreateInstance(std::string name, Shader* shader);
public:
	WaterMaterial(std::string shader) : Material(shader) {}
	WaterMaterial(std::string name, Shader* shader);
	
	void Update();

	utils::ocean::OceanSimulator* GetOceanSim();
	utils::ocean::OceanParameter* GetOceanParams();

	void UpdateAim(math::Vector2 pos, math::Vector2 right, float pow, float angle, int side);

	~WaterMaterial();
private:
	bool play;
	struct MaterialProperties
	{
		math::Color waterColor;
		math::Color skyColor;
		float shininess;
		float uvScale;
		float uvOffset;
		float texelLengthX2;
		math::Vector3 bendParam;
		float g_PerlinSize;
		math::Vector3 g_PerlinAmplitude;
		float radius;
		math::Vector3 g_PerlinOctave;
		int aiming;
		math::Vector3 g_PerlinGradient;
		float pad3;
		math::Vector2 perlinMovement;
		math::Vector2 aimPos;
	};
	float time;
	float timeSinceLastUpdate;
	utils::ocean::OceanParameter m_oceanSettings;
	utils::ocean::OceanSimulator* m_oceanSim;
	MaterialProperties m_materialProperties;

};

