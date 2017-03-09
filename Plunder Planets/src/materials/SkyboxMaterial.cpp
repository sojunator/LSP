#include "SkyboxMaterial.h"
#include "Input.h"

Material * SkyboxMaterial::CreateInstance(std::string name, Shader * shader)
{
	return new SkyboxMaterial(name, shader);
}

Material * SkyboxMaterial::CreateInstance(std::string dir, std::string name, aiMaterial * material, Shader* shader)
{
	return new SkyboxMaterial(dir, name, material, shader);
}


SkyboxMaterial::SkyboxMaterial(std::string name, Shader* shader) : Material(name, shader)
{
//	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 4, Texture::TextureType::CUBEMAP, path));
	//m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 5, Texture::TextureType::CUBEMAP, path));
}

SkyboxMaterial::SkyboxMaterial(std::string dir, std::string name, aiMaterial * material, Shader * shader) : Material(name, shader)
{

}

void SkyboxMaterial::Update()
{

}

SkyboxMaterial::~SkyboxMaterial()
{

}
