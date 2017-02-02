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
			The light look down its forward transformation
			*/
			DirectionalLight::DirectionalLight(GameObject* gameObject) : Light(gameObject)
			{
				//standard init of light
				m_thisLight.lightDirection = m_gameObject->m_transform->Forward();
				m_thisLight.lightColor = thomas::math::Vector4(1, 1, 1, 1);

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

			bool DirectionalLight::SetLightColor(thomas::math::Vector4 other)
			{
				m_thisLight.lightColor = other;
				return thomas::graphics::LightManager::UpdateDirectionalLight(m_thisLight, m_index);
				
			}
			
			
			void DirectionalLight::Update()
			{
				
				m_thisLight.lightDirection = m_gameObject->m_transform->Forward();
				thomas::graphics::LightManager::UpdateDirectionalLight(m_thisLight, m_index);
				return;
			}
			

			/**
			POINT LIGHT
			*/
			PointLight::PointLight(GameObject* gameObject) : Light(gameObject)
			{
				//standard init of light
				m_thisLight.constantAttenuation = 0.6;
				m_thisLight.linearAttenuation = 0.3;
				m_thisLight.quadraticAttenuation = 0.1;
				m_thisLight.lightRange = 5;
				
				m_thisLight.position = thomas::math::Vector3(0, 0, 0);
				m_thisLight.lightColor = thomas::math::Vector4(1, 1, 1, 1);

				m_index = graphics::LightManager::AddPointLight(m_thisLight);
			}
			PointLight::~PointLight()
			{
			}

			bool PointLight::Bind()
			{
				return true;
			}

			bool PointLight::SetLightColor(thomas::math::Vector4 other)
			{
				m_thisLight.lightColor = other;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}
			

			
			bool PointLight::SetAttenuation(float otherConstantAttenuation, float otherLinearAttenuation, float otherQuadraticAttenuation)
			{
				m_thisLight.constantAttenuation = otherConstantAttenuation;
				m_thisLight.linearAttenuation = otherLinearAttenuation;
				m_thisLight.quadraticAttenuation = otherQuadraticAttenuation;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}

			
			bool PointLight::SetLightRange(float otherLightRange)
			{
				m_thisLight.lightRange = otherLightRange;
				return thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
			}
			void PointLight::Update()
			{
				m_thisLight.position = m_gameObject->m_transform->GetPosition();
				
				thomas::graphics::LightManager::UpdatePointLight(m_thisLight, m_index);
				return;
			}
		}
	}
}