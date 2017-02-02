#include "WaterMaterial.h"
#include "Input.h"
Material * WaterMaterial::CreateInstance(std::string name, Shader * shader)
{
	return new WaterMaterial(name, shader);
}


WaterMaterial::WaterMaterial(std::string name, Shader* shader) : Material(name, shader)
{


	m_oceanSim = new utils::OceanSimulator(m_oceanSettings);
	
	m_oceanSim->Update(0);
//	m_shaderTopology = D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST;
	//m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::HEIGHT_MAP, "../res/textures/Wavy_Water - Height.png"));


	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::DIFFUSE, "Ocean", m_oceanSim->GetDisplacementMap(), NULL));

	//m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::NORMAL, "../res/textures/Wavy_Water - Height (Normal Map).png"));
//	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::DIFFUSE, "../res/textures/Wavy_Water - Specular.png"));
	m_materialProperties.uvScale = 1.0/ m_oceanSettings.patchLength;
	m_materialProperties.uvOffset = 0.5f / m_oceanSettings.mapDimension;
	m_materialProperties.texelLengthX2 = m_oceanSettings.patchLength / m_oceanSettings.mapDimension * 2;

	m_materialProperties.ambientColor = math::Color(1.0, 1.0, 1.0);
	m_materialProperties.diffuseColor = math::Color(1.0, 1.0, 1.0);
	m_materialProperties.specularColor = math::Color(1.0, 1.0, 1.0);
	m_materialProperties.specularPower = 10.0 / 1000.0;

	m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
}

void WaterMaterial::Update()
{
	//m_materialProperties.time += Time::GetDeltaTime()*0.01f;

	m_oceanSim->Update(Time::GetDeltaTime());
	m_textures[0]->SetTextureView(m_oceanSim->GetDisplacementMap());
	utils::D3d::FillBuffer(m_materialPropertiesBuffer, m_materialProperties);
}

WaterMaterial::~WaterMaterial()
{
	delete m_oceanSim;
}
