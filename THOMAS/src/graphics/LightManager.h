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

				thomas::math::Vector3 lightDirection;
				float padding;
			};
			struct PointLightStruct
			{
				float attenuationFactor;
				int padding;
				int paading;
				int aasdf;
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
			

			static bool BindAllLights();
			static bool Unbind();

			static bool BindDirectionalLight(unsigned int index);
			static bool BindPointLight(unsigned int index);

			
		private:
			static ID3D11Buffer* s_lightBuffer;
		};

		

	}
}