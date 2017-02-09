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
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 0, "../res/textures/Ground1.jpg"));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 1, "../res/textures/ground-grass1.jpg"));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 2, "../res/textures/hills.jpg"));
}

TerrainMaterial::TerrainMaterial(std::string dir, std::string name, aiMaterial * material, Shader * shader) : Material(name, shader)
{

}

void TerrainMaterial::Update()
{

}

TerrainMaterial::~TerrainMaterial()
{

}
