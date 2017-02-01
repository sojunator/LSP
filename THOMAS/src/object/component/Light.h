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
				virtual bool SetAmbientColor(thomas::math::Vector4 otherAmbientColor) = 0;
				virtual bool SetDiffuseColor(thomas::math::Vector4 otherDiffuseColor) = 0;
				virtual bool SetSpecularColor(thomas::math::Vector4 otherSpecularColor) = 0;

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

				bool SetAmbientColor(thomas::math::Vector4 otherAmbientColor);
				bool SetDiffuseColor(thomas::math::Vector4 otherDiffuseColor);
				bool SetSpecularColor(thomas::math::Vector4 otherSpecularColor);

				bool Bind();
			private:
				int m_index;
				graphics::LightManager::DirectionalLightStruct m_thisLight;
			};

			class THOMAS_API PointLight : public Light
			{
			public:
				PointLight(GameObject* gameObject);
				~PointLight();

				bool SetAmbientColor(thomas::math::Vector4 otherAmbientColor);
				bool SetDiffuseColor(thomas::math::Vector4 otherDiffuseColor);
				bool SetSpecularColor(thomas::math::Vector4 otherSpecularColor);

				bool Bind();
			private:
				int m_index;
				graphics::LightManager::PointLightStruct m_thisLight;
			};
			
		}
	}


}