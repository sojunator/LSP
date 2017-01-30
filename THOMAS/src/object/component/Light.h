#pragma once

#include "Component.h"

#include "../../utils/Math.h"
#include "../GameObject.h"
#include "../../graphics/Shader.h"
#include "../../utils/d3d.h"
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
				bool m_updateLightBuffer();

			public:
				Light(GameObject* gameObject);// , thomas::math::Vector4 otherAmbient, thomas::math::Vector4 otherDiffuse, thomas::math::Vector4 otherSpecular);
				
				~Light();

				
				
				bool Bind();
				bool Unbind();

				void SetAmbientColor(thomas::math::Vector4 other);
				void SetDiffuseColor(thomas::math::Vector4 other);
				void SetSpecularColor(thomas::math::Vector4 other);
				void SetLightDirection(thomas::math::Vector3 other);




			private:
				

				struct lightStruct
				{
					thomas::math::Vector4 ambientColor;
					thomas::math::Vector4 diffuseColor;
					thomas::math::Vector4 specularColor;


					thomas::math::Vector3 lightDir;
					float padding;
				} m_lightstruct;
				
				ID3D11Buffer* m_lightBuffer;
			};
		}
	}


}