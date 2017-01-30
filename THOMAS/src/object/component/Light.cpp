#include "Light.h"


namespace thomas
{
	namespace object
	{
		namespace component
		{
			
			
			Light::Light(GameObject* gameObject): Component("LightComponent", gameObject)
			{
				
				//TEMP
				m_lightstruct.ambientColor = thomas::math::Vector4(0.5, 0, 0, 1);
				m_lightstruct.diffuseColor = thomas::math::Vector4(1, 0, 0, 1);
				m_lightstruct.specularColor = thomas::math::Vector4(1, 0, 0, 1);
				m_lightstruct.lightDir = thomas::math::Vector3(-1, 0, 0);
				m_lightstruct.padding = 0;
				//---
				
				m_updateLightBuffer();
			};

			bool Light::m_updateLightBuffer()
			{
				if (!m_lightBuffer)
					m_lightBuffer = thomas::utils::D3d::CreateBufferFromStruct(m_lightstruct, D3D11_BIND_CONSTANT_BUFFER);
				else
					thomas::utils::D3d::FillBuffer(m_lightBuffer, m_lightstruct);
				

				return true;
			}

			bool Light::Bind()
			{
				return graphics::Shader::GetCurrentBoundShader()->BindBuffer(m_lightBuffer, thomas::graphics::Shader::ResourceType::LIGHTS);

			}

			bool Light::Unbind()
			{

				return graphics::Shader::GetCurrentBoundShader()->BindBuffer(NULL, thomas::graphics::Shader::ResourceType::LIGHTS);
			}


			void Light::SetAmbientColor(thomas::math::Vector4 other)
			{
				m_lightstruct.ambientColor = other;
			}
			void Light::SetDiffuseColor(thomas::math::Vector4 other)
			{
				m_lightstruct.diffuseColor = other;
			}
			void Light::SetSpecularColor(thomas::math::Vector4 other)
			{
				m_lightstruct.specularColor = other;
			}
			void Light::SetLightDirection(thomas::math::Vector3 other)
			{
				m_lightstruct.lightDir = other;
			}
		}
	}
}