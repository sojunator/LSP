#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace graphics;

class WaterMaterial : public Material
{
private:
	Material* CreateInstance(std::string name, Shader* shader);
	Material* CreateInstance(std::string dir, std::string name, aiMaterial* material, Shader* shader);
public:
	WaterMaterial(std::string shader) : Material(shader) {}
	WaterMaterial(std::string name, Shader* shader);
	WaterMaterial(std::string dir, std::string name, aiMaterial* material, Shader* shader);
	
	void Update();

	~WaterMaterial() {};
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
	MaterialProperties m_materialProperties;

};

