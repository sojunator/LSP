#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace graphics;

class SkyboxMaterial : public Material
{
private:
	Material* CreateInstance(std::string name, Shader* shader);
	Material* CreateInstance(std::string dir, std::string name, aiMaterial* material, Shader* shader);
public:
	SkyboxMaterial(std::string shader) : Material(shader) {}
	SkyboxMaterial(std::string name, Shader* shader);
	SkyboxMaterial(std::string dir, std::string name, aiMaterial* material, Shader* shader);

	void Update();

	~SkyboxMaterial();
private:
	struct MaterialProperties
	{
		math::Color ambientColor;
		math::Color diffuseColor;
		math::Color specularColor;
		float specularPower;
		float tess;
		math::Vector2 padding;
	};
	MaterialProperties m_materialProperties;

};