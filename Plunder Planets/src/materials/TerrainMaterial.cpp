#include "TerrainMaterial.h"
#include "Input.h"
Material * TerrainMaterial::CreateInstance(std::string name, Shader * shader)
{
	return new TerrainMaterial(name, shader);
}

Material * TerrainMaterial::CreateInstance(std::string dir, std::string name, aiMaterial * material, Shader* shader)
{
	return new TerrainMaterial(dir, name, material, shader);
}


TerrainMaterial::TerrainMaterial(std::string name, Shader* shader) : Material(name, shader)
{
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::DIFFUSE, "../res/dearleader.jpg"));
}

TerrainMaterial::TerrainMaterial(std::string dir, std::string name, aiMaterial * material, Shader * shader) : Material(name, shader)
{


	m_textures = utils::AssimpLoader::GetMaterialTextures(material, dir);

	m_materialProperties.ambientColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT);
	m_materialProperties.diffuseColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE);
	m_materialProperties.specularColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR);
	m_materialProperties.specularPower = utils::AssimpLoader::GetMaterialShininess(material) / 1000.0;

	//m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::CLAMP, Texture::TextureType::HEIGHT_MAP, "../res/height_map.png"));

	m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
}

void TerrainMaterial::Update()
{

}

TerrainMaterial::~TerrainMaterial()
{

}
