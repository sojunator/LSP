#pragma once
#include "Thomas.h"
#include "utils\OceanSimulator.h"
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
		math::Color ambientColor;
		math::Color diffuseColor;
		math::Color specularColor;
		float specularPower;
		float tess;
		float time;
		float padding;
	};
	
	utils::OceanSimulator::OceanSettings m_oceanSettings;
	utils::OceanSimulator* m_oceanSim;
	MaterialProperties m_materialProperties;

};

