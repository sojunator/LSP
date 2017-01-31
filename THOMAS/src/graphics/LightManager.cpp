#include "LightManager.h"


namespace thomas
{
	namespace graphics
	{
		LightManager::LightManager()
		{
		}

		LightManager::~LightManager()
		{
		}

		LightManager::LightBufferStruct LightManager::s_lightstruct;
		ID3D11Buffer* LightManager::s_lightBuffer;
		bool LightManager::UpdateLightBuffer()
		{
			if (!s_lightBuffer)
			{
				s_lightBuffer = thomas::utils::D3d::CreateBufferFromStruct(s_lightstruct, D3D11_BIND_CONSTANT_BUFFER);
				return true;
			}
			else
				return thomas::utils::D3d::FillBuffer(s_lightBuffer, s_lightstruct);

		}
		bool LightManager::BindAllLights()
		{
			return graphics::Shader::GetCurrentBoundShader()->BindBuffer(s_lightBuffer, thomas::graphics::Shader::ResourceType::LIGHTS);
		}

		bool LightManager::Unbind()
		{
			return graphics::Shader::GetCurrentBoundShader()->BindBuffer(NULL, thomas::graphics::Shader::ResourceType::LIGHTS);
		}

		bool LightManager::AddDirectionalLight(DirectionalLightStruct directionalLight)
		{
			int maxlength = sizeof(s_lightstruct.directionalLights) / sizeof(DirectionalLightStruct);
			if (maxlength > s_lightstruct.nrOfDirectionalLights)
			{
				s_lightstruct.directionalLights[s_lightstruct.nrOfDirectionalLights] = directionalLight;
				s_lightstruct.nrOfDirectionalLights++;
				UpdateLightBuffer();
				return true;
			}
			else//to many lights
				return false;

		}

		bool LightManager::AddPointLight()
		{
			return true;
		}
	}
}