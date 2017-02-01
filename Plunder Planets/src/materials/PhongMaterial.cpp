#include "PhongMaterial.h"


PhongMaterial::PhongMaterial(std::string dir, std::string name, aiMaterial* material, Shader* shader) : Material(name, shader)
{
	m_textures = utils::AssimpLoader::GetMaterialTextures(material, dir);

	m_materialProperties.ambientColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT);
	m_materialProperties.diffuseColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE);
	m_materialProperties.specularColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR);
	m_materialProperties.specularPower = utils::AssimpLoader::GetMaterialShininess(material) / 1000.0;


	m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);

}
Material * PhongMaterial::CreateInstance(std::string dir, std::string name, aiMaterial * material, Shader* shader)
{
	return new PhongMaterial(dir, name, material, shader);
}
