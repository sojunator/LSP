#include "WaterMaterial.h"
#include "Input.h"
Material * WaterMaterial::CreateInstance(std::string name, Shader * shader)
{
	return new WaterMaterial(name, shader);
}

Material * WaterMaterial::CreateInstance(std::string dir, std::string name, aiMaterial * material, Shader* shader)
{
	return new WaterMaterial(dir, name, material, shader);
}


WaterMaterial::WaterMaterial(std::string name, Shader* shader) : Material(name, shader)
{
	m_shaderTopology = D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST;
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::HEIGHT_MAP, "../res/height_map.jpg"));
	m_materialProperties.tess = 1.0;
	m_materialProperties.time = 0.0;
	m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
}

WaterMaterial::WaterMaterial(std::string dir, std::string name, aiMaterial * material, Shader * shader) : Material(name, shader)
{

	m_shaderTopology = D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST;

	m_textures = utils::AssimpLoader::GetMaterialTextures(material, dir);

	m_materialProperties.ambientColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT);
	m_materialProperties.diffuseColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE);
	m_materialProperties.specularColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR);
	m_materialProperties.specularPower = utils::AssimpLoader::GetMaterialShininess(material) / 1000.0;
	m_materialProperties.tess = 1.0;

	//m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::CLAMP, Texture::TextureType::HEIGHT_MAP, "../res/height_map.png"));

	m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
}

void WaterMaterial::Update()
{
	m_materialProperties.time += Time::GetDeltaTime()*0.01f;
	if (Input::GetKeyDown(Input::Keys::K))
	{
		m_materialProperties.tess += 1.0;
		
	}
	utils::D3d::FillBuffer(m_materialPropertiesBuffer, m_materialProperties);
}
