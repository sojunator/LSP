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
	void SetAim(float side) { m_materialProperties.aiming = side; }

	utils::ocean::OceanSimulator* GetOceanSim();
	utils::ocean::OceanParameter* GetOceanParams();

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
		float pad1;
		math::Vector3 g_PerlinOctave;
		float pad2;
		math::Vector3 g_PerlinGradient;
		float pad3;
		math::Vector2 perlinMovement;
		math::Vector2 pad4;
		math::Vector3 shipPosition;
		float aiming; //-1 for left side, 1 for right, 0 when not aiming
		math::Vector3 shipRight;
		float power; //TODO: f� hj�lp med shader
	};
	float time;
	float timeSinceLastUpdate;
	utils::ocean::OceanParameter m_oceanSettings;
	utils::ocean::OceanSimulator* m_oceanSim;
	MaterialProperties m_materialProperties;

};

