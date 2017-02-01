#include "Light.h"


namespace thomas
{
	namespace object
	{
		namespace component
		{

			Light::Light(GameObject* gameObject) : Component("LightComponent", gameObject)
			{
			}
			Light::~Light()
			{
			}
			
			/**
			DIRECTIONAL LIGHT
			*/
			DirectionalLight::DirectionalLight(GameObject* gameObject) : Light(gameObject)
			{
				//standard init of light
				m_thisLight.lightDirection = thomas::math::Vector4(0, 0, -1, 0);
				m_thisLight.ambientColor = thomas::math::Vector4(0, 0, 0, 1);
				m_thisLight.diffuseColor = thomas::math::Vector4(1, 1, 1, 1);
				m_thisLight.specularColor = thomas::math::Vector4(1, 1, 1, 1);

				m_index = graphics::LightManager::AddDirectionalLight(m_thisLight);

				/*if ((m_index = graphics::LightManager::AddDirectionalLight(m_thisLight)) < 0)
				{
					LOG("Cant add light")
					Destroy(this);
				}*/
				
				
			}

			DirectionalLight::~DirectionalLight()
			{
			}

			bool DirectionalLight::Bind()
			{
				return true;
			}

			bool DirectionalLight::SetAmbientColor(thomas::math::Vector4 otherAmbientColor)
			{
				m_thisLight.ambientColor = otherAmbientColor;
				return thomas::graphics::LightManager::UpdateDirectionalLight(m_thisLight, m_index);
				
			}
			bool DirectionalLight::SetDiffuseColor(thomas::math::Vector4 otherDiffuseColor)
			{
				m_thisLight.diffuseColor = otherDiffuseColor;
				return thomas::graphics::LightManager::UpdateDirectionalLight(m_thisLight, m_index);
			}
			bool DirectionalLight::SetSpecularColor(thomas::math::Vector4 otherSpecularColor)
			{
				m_thisLight.specularColor = otherSpecularColor;
				return thomas::graphics::LightManager::UpdateDirectionalLight(m_thisLight, m_index);
			}

			bool DirectionalLight::SetDirection(thomas::math::Vector4 otherLightDirection)
			{
				m_thisLight.lightDirection = otherLightDirection;
				return thomas::graphics::LightManager::UpdateDirectionalLight(m_thisLight, m_index);
			}

			/**
			POINT LIGHT
			*/
			PointLight::PointLight(GameObject* gameObject) : Light(gameObject)
			{
				//standard init of light
				m_thisLight.attenuationFactor = 5;
				
				m_thisLight.position = thomas::math::Vector4(3, 3, 3, 0);
				m_thisLight.ambientColor = thomas::math::Vector4(0, 0, 0, 1);
				m_thisLight.diffuseColor = thomas::math::Vector4(1, 1, 1, 1);
				m_thisLight.specularColor = thomas::math::Vector4(1, 1, 1, 1);

				m_index = graphics::LightManager::AddPointLight(m_thisLight);
			}
			PointLight::~PointLight()
			{
			}

			bool PointLight::Bind()
			{
				return true;
			}

			bool PointLight::SetAmbientColor(thomas::math::Vector4 otherAmbientColor)
			{
				m_thisLight.ambientColor = otherAmbientColor;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}
			bool PointLight::SetDiffuseColor(thomas::math::Vector4 otherDiffuseColor)
			{
				m_thisLight.diffuseColor = otherDiffuseColor;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}
			bool PointLight::SetSpecularColor(thomas::math::Vector4 otherSpecularColor)
			{
				m_thisLight.specularColor = otherSpecularColor;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}

			bool PointLight::SetPosition(thomas::math::Vector4 otherPosition)
			{
				m_thisLight.position = otherPosition;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}
			bool PointLight::SetAttenuationFactor(int otherAttenuationFactor)
			{
				m_thisLight.attenuationFactor = otherAttenuationFactor;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}
		}
	}
}