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
				PointLightStruct pointLights[1];
			} static s_lightstruct;

			static ID3D11Buffer* s_lightBuffer;//<-----------------------------------------------------------release

			
			LightManager();
			~LightManager();
			static bool AddDirectionalLight(DirectionalLightStruct directionalLight);
			static bool AddPointLight();

			static bool BindAllLights();
			static bool Unbind();

			
		private:

		};

		

	}
}