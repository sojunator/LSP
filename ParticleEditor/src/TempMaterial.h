#pragma once
#include "Thomas.h"
using namespace thomas;
using namespace graphics;
class TempMaterial : public Material
{
private:
	Material* CreateInstance(std::string dir, std::string name, aiMaterial* material, Shader* shader)
	{
		return new TempMaterial(dir, name, material, shader);
	}
public:
	TempMaterial(std::string shader) : Material(shader) {}
	TempMaterial(std::string dir, std::string name, aiMaterial* material, Shader* shader) : Material(name, shader)
	{
		m_textures = utils::AssimpLoader::GetMaterialTextures(material, dir);
		m_materialProperties.materialProperty = math::Vector4(0, 0, 0, 0);

		for (unsigned int i = 0; i < m_textures.size(); i++)
		{
			switch (m_textures[i]->GetTextureType())
			{
			case Texture::TextureType::DIFFUSE:
				m_materialProperties.materialProperty.x = 1;
				break;
			case Texture::TextureType::SPECULAR:
				m_materialProperties.materialProperty.y = 1;
				break;
			case Texture::TextureType::NORMAL:
				m_materialProperties.materialProperty.z = 1;
				break;
			}
		}

		m_materialProperties.ambientColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT);
		m_materialProperties.diffuseColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE);
		m_materialProperties.specularColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR);
		m_materialProperties.specularPower = utils::AssimpLoader::GetMaterialShininess(material);


		m_materialPropertiesBuffer = utils::D3d::CreateDynamicBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
	}

	~TempMaterial()
	{

	}

private:
	struct MaterialProperties
	{
		math::Color ambientColor;
		math::Color diffuseColor;
		math::Color specularColor;
		math::Vector4 materialProperty;
		float specularPower;
		math::Vector3 padding;
	};

	MaterialProperties m_materialProperties;
};
