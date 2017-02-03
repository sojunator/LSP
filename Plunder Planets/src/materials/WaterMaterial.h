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

	~WaterMaterial();
private:
	struct MaterialProperties
	{
		math::Color waterColor;
		math::Color skyColor;
		float shininess;
		float uvScale;
		float uvOffset;
		float texelLengthX2;
	};
	float time;
	utils::ocean::OceanParameter m_oceanSettings;
	utils::ocean::OceanSimulator* m_oceanSim;
	MaterialProperties m_materialProperties;

};

