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
				Light(GameObject* gameObject);
				~Light();

				
				
			};


			class THOMAS_API DirectionalLight : public Light
			{
			public:
				DirectionalLight(GameObject* gameObject);
				~DirectionalLight();

				//bindDirectionalLights()
			private:
				
				graphics::LightManager::DirectionalLightStruct thisLight;
			};

			
			
		}
	}


}