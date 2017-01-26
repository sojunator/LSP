#include "Material.h"

namespace thomas
{
	namespace graphics
	{
		namespace material
		{
			static std::vector<Material*> s_materials;

			Material::Material()
			{
			}


			Material::~Material()
			{
			}

			Material* Material::CreateMaterial(aiMaterial * material)
			{
				return nullptr;
			}

			Material* Material::GetMaterialByName(std::string name)
			{
				for (unsigned int i = 0; i < s_materials.size(); i++)
				{
					if (s_materials[i]->GetName() == name)
					{
						return s_materials[i];
					}
				}
				
				return NULL;
			}

			std::vector<Material*> Material::GetLoadedMaterials()
			{
				return std::vector<Material*>();
			}

			std::vector<Material*> Material::GetMaterialsByShaders(Shader * shader)
			{
				return std::vector<Material*>();
			}

			std::vector<Material*> Material::GetMaterialsByShaders(std::string name)
			{
				return std::vector<Material*>();
			}

			std::string Material::GetName()
			{
				return m_materialName;
			}

			Shader* Material::GetShader()
			{
				Shader* shader;
				return shader;
			}
		}
	}
}
