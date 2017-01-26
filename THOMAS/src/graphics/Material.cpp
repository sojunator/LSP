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
				return s_materials;
			}

			std::vector<Material*> Material::GetMaterialsByShaders(Shader * shader)
			{
				std::vector<Material*> materials;

				for (unsigned int i = 0; i < s_materials.size(); i++)
				{
					if (s_materials[i]->GetShader() == shader)
					{
						materials.push_back(s_materials[i]);
					}
				}
				return materials;
			}

			std::vector<Material*> Material::GetMaterialsByShaders(std::string name)
			{
				std::vector<Material*> materials;

				for (unsigned int i = 0; i < s_materials.size(); i++)
				{
					if (s_materials[i]->GetShader()->GetName() == name)
					{
						materials.push_back(s_materials[i]);
					} 
				}
				return materials;
			}

			std::string Material::GetName()
			{
				return m_materialName;
			}

			Shader* Material::GetShader()
			{
				return m_shader;
			}
		}
	}
}
