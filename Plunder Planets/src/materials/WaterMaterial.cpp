#include "WaterMaterial.h"
#include "Input.h"
#include "graphics\Renderer.h"
#include "..\gameobjects\Ship.h"
Material * WaterMaterial::CreateInstance(std::string name, Shader * shader)
{
	return new WaterMaterial(name, shader);
}


WaterMaterial::WaterMaterial(std::string name, Shader* shader) : Material(name, shader)
{
	m_pow = 1150.f; //completely arbitrary
	m_tweakConst = -100.f; //same as above
	// The size of displacement map. In this sample, it's fixed to 512.
	m_oceanSettings.dmap_dim = 512;
	// The side length (world space) of square patch
	m_oceanSettings.patch_length = 1000.0f;
	// Adjust this parameter to control the simulation speed

	// A scale to control the amplitude. Not the world space height
	m_oceanSettings.wave_amplitude = 0.35f;
	// 2D wind direction. No need to be normalized
	m_oceanSettings.wind_dir = math::Vector2(0.8f, 0.6f);
	// The bigger the wind speed, the larger scale of wave crest.
	// But the wave scale can be no larger than patch_length
	m_oceanSettings.wind_speed = 200.0f;
	// Damp out the components opposite to wind direction.
	// The smaller the value, the higher wind dependency
	m_oceanSettings.wind_dependency = 0.07f;
	// Control the scale of horizontal movement. Higher value creates
	// pointy crests.

	m_oceanSettings.choppy_scale = 0.8f;
	m_oceanSettings.time_scale = 0.12f;

	m_oceanSim = new utils::ocean::OceanSimulator(m_oceanSettings, ThomasCore::GetDevice());

	m_oceanSim->updateDisplacementMap(0);

	m_oceanSettings.patch_length /= 2;

	m_shaderTopology = D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST;
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::DIFFUSE, "../res/textures/perlin.dds"));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::HEIGHT_MAP, "OceanDisplacement", m_oceanSim->getD3D11DisplacementMap()));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::NORMAL, "OceanNormal", m_oceanSim->getD3D11GradientMap()));
	m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::SPECULAR, "../res/textures/foam.png"));
	
	m_materialProperties.uvScale = 1.0 / m_oceanSettings.patch_length;
	m_materialProperties.uvOffset = 0.5f / m_oceanSettings.dmap_dim;
	m_materialProperties.texelLengthX2 = m_oceanSettings.patch_length / m_oceanSettings.dmap_dim * 2;

	m_materialProperties.skyColor = math::Color(0.38f, 0.45f, 0.56f);
	m_materialProperties.waterColor = math::Color(0.07f, 0.15f, 0.2f, 1.0);
	m_materialProperties.shininess = 0.7;
	m_materialProperties.bendParam = math::Vector3(0.1f, -0.4f, 0.2f);


	m_materialProperties.g_PerlinSize = 0.0001;
	m_materialProperties.g_PerlinAmplitude = math::Vector3(35, 42, 57)*0.5;
	m_materialProperties.g_PerlinOctave = math::Vector3(1.12f, 0.59f, 0.23f)*0.001;
	m_materialProperties.g_PerlinGradient = math::Vector3(1.4f, 1.6f, 2.2f);
	m_materialProperties.perlinMovement = -m_oceanSettings.wind_dir*time*0.06;

	m_materialProperties.aimPos = math::Vector2(0, 0);
	m_materialProperties.radius = 10.f;
	m_materialProperties.aiming = 0;

	m_materialPropertiesBuffer = utils::D3d::CreateDynamicBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
	play = true;
}

void WaterMaterial::Update()
{
	timeSinceLastUpdate += Time::GetDeltaTime();
	m_materialProperties.perlinMovement = -m_oceanSettings.wind_dir*time*0.06;
	time += Time::GetDeltaTime();

	if (timeSinceLastUpdate > 0.05 && play)
	{
		timeSinceLastUpdate = 0;
		m_oceanSim->updateDisplacementMap(time);
	}

	
	if (Input::GetKeyDown(Input::Keys::C))
		play = !play;

	m_materialProperties.perlinMovement = -m_oceanSettings.wind_dir*time*0.01;
	utils::D3d::FillDynamicBufferStruct(m_materialPropertiesBuffer, m_materialProperties);

}

utils::ocean::OceanSimulator * WaterMaterial::GetOceanSim()
{
	return m_oceanSim;
}

utils::ocean::OceanParameter * WaterMaterial::GetOceanParams()
{
	return &m_oceanSettings;
}
void WaterMaterial::UpdateAim(math::Vector2 pos, math::Vector2 target)
{
//	m_materialProperties.aimPos = pos + right * ((std::sqrtf(std::sinf(angle)) * m_pow) + (std::sinf(angle) * m_tweakConst));
	m_materialProperties.aimPos = target;
	math::Vector3 distance = pos - target;
	m_materialProperties.radius = std::sqrt(distance.Length())*2;
	m_materialProperties.aiming = 1;
}
void WaterMaterial::DisableAim()
{
	m_materialProperties.aiming = 0;
}

WaterMaterial::~WaterMaterial()
{
	delete m_oceanSim;
}
