#include "Light.h"


namespace thomas
{
	namespace object
	{
		namespace component
		{

			Light::Light(GameObject* gameObject) : Component("LightComponent", gameObject)
			{/*
				m_lightstruct.nrOfDirectionalLights = 0;
				m_lightstruct.nrOfPointLights = 0;
				m_lightstruct.padding1 = 0;
				m_lightstruct.padding2 = 0;*/
			}
			Light::~Light()
			{

			}

			

			DirectionalLight::DirectionalLight(GameObject* gameObject) : Light(gameObject)
			{
				thisLight.lightDirection = thomas::math::Vector4(0, 0, -1, 0);
				thisLight.ambientColor = thomas::math::Vector4(0, 0, 0, 1);
				thisLight.diffuseColor = thomas::math::Vector4(1, 1, 1, 1);
				thisLight.specularColor = thomas::math::Vector4(1, 1, 1, 1);

				graphics::LightManager::AddDirectionalLight(thisLight);
			}

			DirectionalLight::~DirectionalLight()
			{
			}
			
			
		}
	}
}