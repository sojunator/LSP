#pragma once
#include "../utils/Math.h"
#include "../utils/d3d.h"
#include "../graphics/Shader.h"

namespace thomas
{
	namespace graphics
	{

		class LightManager
		{
		private:
			static bool UpdateLightBuffer();
		public:
			//make struct for colors?
			//struct....


			//match these structs on the graphicscard
			struct DirectionalLightStruct
			{
				thomas::math::Vector4 ambientColor;
				thomas::math::Vector4 diffuseColor;
				thomas::math::Vector4 specularColor;

				thomas::math::Vector4 lightDirection;
			};
			struct PointLightStruct
			{
				thomas::math::Vector4 ambientColor;
				thomas::math::Vector4 diffuseColor;
				thomas::math::Vector4 specularColor;

				thomas::math::Vector4 position;
			};
			struct LightBufferStruct
			{
				int nrOfDirectionalLights;
				int nrOfPointLights;
				int padding1;
				int padding2;
				DirectionalLightStruct directionalLights[3];
				PointLightStruct pointLights[3];
			} static s_lightstruct;

			

			
			LightManager();
			~LightManager();
			static int AddDirectionalLight(DirectionalLightStruct directionalLight);
			
			static int AddPointLight(PointLightStruct pointLight);

			static bool UpdateDirectionalLight(DirectionalLightStruct other, int index);
			static bool UpdatePointLight(PointLightStruct other, int index);
			/*template<typename T>
			static bool UpdateLight(T lightStruct, int index)
			{
				if (dynamic_cast<DirectionalLightStruct*>(lightStruct))
				{
					s_lightstruct.directionalLights[index] = *lightStruct;
				}
				else if (dynamic_cast<PointLightStruct*>(lightStruct))
				{
					s_lightstruct.pointLights[index] = *lightStruct;
				}
				else
				{
					LOG("Invalid lighttype");
					return false;
				}
			}*/

			static bool BindAllLights();
			static bool Unbind();

			static bool BindDierctionalLight(unsigned int index);
			static bool BindPointLight(unsigned int index);

			
		private:
			static ID3D11Buffer* s_lightBuffer;
		};

		

	}
}