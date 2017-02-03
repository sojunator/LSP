#include "WaterMaterial.h"
#include "Input.h"
Material * WaterMaterial::CreateInstance(std::string name, Shader * shader)
{
	return new WaterMaterial(name, shader);
}


WaterMaterial::WaterMaterial(std::string name, Shader* shader) : Material(name, shader)
{

	// The size of displacement map. In this sample, it's fixed to 512.
	m_oceanSettings.dmap_dim = 512;
	// The side length (world space) of square patch
	m_oceanSettings.patch_length = 2000.0f;
	// Adjust this parameter to control the simulation speed
	m_oceanSettings.time_scale = 0.8f;
	// A scale to control the amplitude. Not the world space height
	m_oceanSettings.wave_amplitude = 0.35f;
	// 2D wind direction. No need to be normalized
	m_oceanSettings.wind_dir = math::Vector2(0.8f, 0.6f);
	// The bigger the wind speed, the larger scale of wave crest.
	// But the wave scale can be no larger than patch_length
	m_oceanSettings.wind_speed = 600.0f;
	// Damp out the components opposite to wind direction.
	// The smaller the value, the higher wind dependency
	m_oceanSettings.wind_dependency = 0.07f;
	// Control the scale of horizontal movement. Higher value creates
	// pointy crests.
	m_oceanSettings.choppy_scale = 1.3f;

	m_oceanSim = new utils::ocean::OceanSimulator(m_oceanSettings, ThomasCore::GetDevice());
	
	m_oceanSim->updateDisplacementMap(0);



	m_shaderTopology = D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST;

	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::HEIGHT_MAP, "OceanDisplacement", m_oceanSim->getD3D11DisplacementMap(), NULL));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::NORMAL, "OceanNormal", m_oceanSim->getD3D11GradientMap(), NULL));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::SPECULAR, "OceanFresnel", utils::D3d::CreateFresnel(256, 16.0), NULL));

	m_materialProperties.uvScale = 1.0/ m_oceanSettings.patch_length;
	m_materialProperties.uvOffset = 0.5f / m_oceanSettings.dmap_dim;
	m_materialProperties.texelLengthX2 = m_oceanSettings.patch_length / m_oceanSettings.dmap_dim * 2;

	m_materialProperties.ambientColor = math::Color(1.0, 1.0, 1.0);
	m_materialProperties.diffuseColor = math::Color(1.0, 1.0, 1.0);
	m_materialProperties.specularColor = math::Color(1.0, 1.0, 1.0);
	m_materialProperties.specularPower = 10.0 / 1000.0;


	m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
}

void WaterMaterial::Update()
{
	//m_materialProperties.time += Time::GetDeltaTime()*0.01f;
	time += Time::GetDeltaTime();
	m_oceanSim->updateDisplacementMap(time);
	utils::D3d::FillBuffer(m_materialPropertiesBuffer, m_materialProperties);
}

WaterMaterial::~WaterMaterial()
{
	delete m_oceanSim;
}
