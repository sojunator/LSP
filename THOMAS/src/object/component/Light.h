#pragma once

#include "Component.h"

#include "../../utils/Math.h"
#include "../GameObject.h"
#include "../../graphics/Shader.h"
#include "../../utils/d3d.h"
#include "../../graphics/LightManager.h"

/**
Light class
*/


namespace thomas
{
	namespace object 
	{
		namespace component
		{
			class THOMAS_API Light : public Component
			{

			private:
				
			public:
				virtual bool SetLightColor(thomas::math::Vector4 other) = 0;

				virtual bool Bind() = 0;
			protected:
				Light(GameObject* gameObject);
				~Light();
				
			};


			class THOMAS_API DirectionalLight : public Light
			{
			public:
				DirectionalLight(GameObject* gameObject);
				~DirectionalLight();

				bool SetLightColor(thomas::math::Vector4 other);

				bool Bind();

				void Update();
			private:
				int m_index;
				graphics::LightManager::DirectionalLightStruct m_thisLight;
			};

			class THOMAS_API PointLight : public Light
			{
			public:
				PointLight(GameObject* gameObject);
				~PointLight();

				bool SetLightColor(thomas::math::Vector4 other);
				bool SetAttenuation(float otherConstantAttenuation, float otherLinearAttenuation, float otherQuadraticAttenuation);
				bool SetLightRange(float otherLightRange);

				bool Bind();

				void Update();
				

			private:
				int m_index;
				graphics::LightManager::PointLightStruct m_thisLight;
			};
			
		}
	}


}