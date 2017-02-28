#pragma once
#include "../Ocean/OceanSimulator.h"
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

	ocean::OceanSimulator* GetOceanSim();
	ocean::OceanParameter* GetOceanParams();

	void UpdateAim(math::Vector2 pos, math::Vector2 target);

	void DisableAim();

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
	ocean::OceanParameter m_oceanSettings;
	ocean::OceanSimulator* m_oceanSim;
	MaterialProperties m_materialProperties;

	float m_pow;
	float m_tweakConst;
};

