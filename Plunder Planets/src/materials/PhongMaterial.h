#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace graphics;
class PhongMaterial : public Material
{
private:
	Material* CreateInstance(std::string dir, std::string name, aiMaterial* material);
public:
	PhongMaterial(std::string shader) : Material(shader) {}
	PhongMaterial(std::string dir, std::string name, aiMaterial* material);



	~PhongMaterial();

private:
	struct MaterialProperties
	{
		math::Color ambientColor;
		math::Color diffuseColor;
		math::Color specularColor;
		float specularPower;
		math::Vector3 padding;
	};

	MaterialProperties m_materialProperties;
};
