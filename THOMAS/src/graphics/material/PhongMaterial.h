#pragma once
#include "Material.h"
#include "../../utils/Math.h"
namespace thomas
{
	namespace graphics
	{
		namespace material
		{

			class PhongMaterial : public Material
			{
			private:
			public:
				PhongMaterial(std::string dir, std::string name, aiMaterial* material);
				~PhongMaterial();

			private:
				struct MaterialProperties 
				{
					math::Color ambientColor;
				};

				MaterialProperties m_materialProperties;
			};

		}
	}
}