#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace graphics;

class TerrainMaterial : public Material
{
private:
	Material* CreateInstance(std::string name, Shader* shader);
	Material* CreateInstance(std::string dir, std::string name, aiMaterial* material, Shader* shader);
public:
	TerrainMaterial(std::string shader) : Material(shader) {}
	TerrainMaterial(std::string name, Shader* shader);
	TerrainMaterial(std::string dir, std::string name, aiMaterial* material, Shader* shader);

	void Update();

	~TerrainMaterial();
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

