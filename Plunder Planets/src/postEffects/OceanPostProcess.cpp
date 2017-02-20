#include "OceanPostProcess.h"
#include "../d3d.h"
OceanPostProcess::OceanPostProcess(std::string name, Shader * shader) : PostEffect(name, shader)
{
	// The size of displacement map. In this sample, it's fixed to 512.
	m_oceanSettings.dmap_dim = 512;
	// The side length (world space) of square patch
	m_oceanSettings.patch_length = 256.0f;
	// Adjust this parameter to control the simulation speed

	// A scale to control the amplitude. Not the world space height
	m_oceanSettings.wave_amplitude = 0.55f;
	// 2D wind direction. No need to be normalized
	m_oceanSettings.wind_dir = math::Vector2(0.8f, 0.6f);
	// The bigger the wind speed, the larger scale of wave crest.
	// But the wave scale can be no larger than patch_length
	m_oceanSettings.wind_speed = 100.0f;
	// Damp out the components opposite to wind direction.
	// The smaller the value, the higher wind dependency
	m_oceanSettings.wind_dependency = 0.07f;
	// Control the scale of horizontal movement. Higher value creates
	// pointy crests.

	m_oceanSettings.choppy_scale = 3.0f;
	m_oceanSettings.time_scale = 0.3f;

	m_oceanSim = new utils::ocean::OceanSimulator(m_oceanSettings, ThomasCore::GetDevice());

	m_oceanSim->updateDisplacementMap(0);

	m_oceanSettings.patch_length /= 8;
		
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 1, "depthBuffer", Renderer::GetDepthBufferSRV()));

	//m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::DIFFUSE, "../res/textures/perlin.dds"));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 2, "OceanDisplacement", m_oceanSim->getD3D11DisplacementMap()));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 3, "OceanNormal", m_oceanSim->getD3D11GradientMap()));
	//m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::SPECULAR, "OceanFresnel", utils::D3d::CreateFresnel(1024, 8.0)));

	m_oceanPropertiesStruct.uvScale = 1.0 / m_oceanSettings.patch_length;
	m_oceanPropertiesStruct.uvOffset = 0.5f / m_oceanSettings.dmap_dim;
	m_oceanPropertiesStruct.texelLengthX2 = m_oceanSettings.patch_length / m_oceanSettings.dmap_dim * 2;

	m_oceanPropertiesStruct.skyColor = math::Color(0.38f, 0.45f, 0.56f);
	m_oceanPropertiesStruct.waterColor = math::Color(0.07f, 0.15f, 0.2f, 1.0);
	m_oceanPropertiesStruct.shininess = 200;
	m_oceanPropertiesStruct.bendParam = math::Vector3(0.1f, -0.4f, 0.2f);


	m_oceanPropertiesStruct.g_PerlinSize = 1.0;
	m_oceanPropertiesStruct.g_PerlinAmplitude = math::Vector3(35, 42, 57);
	m_oceanPropertiesStruct.g_PerlinOctave = math::Vector3(1.12f, 0.59f, 0.23f)*0.016;
	m_oceanPropertiesStruct.g_PerlinGradient = math::Vector3(1.4f, 1.6f, 2.2f);
	m_oceanPropertiesStruct.perlinMovement = -m_oceanSettings.wind_dir*time*0.06;

	m_effectProperties = utils::D3d::CreateBufferFromStruct(m_oceanPropertiesStruct, D3D11_BIND_CONSTANT_BUFFER);

}

void OceanPostProcess::Update()
{
	time += Time::GetDeltaTime();
	m_oceanSim->updateDisplacementMap(time);
	utils::D3d::FillBuffer(m_effectProperties, m_oceanPropertiesStruct);
}
