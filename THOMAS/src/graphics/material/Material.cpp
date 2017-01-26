#include "Material.h"
#include "../../utils/AssimpLoader.h"
namespace thomas
{
	namespace graphics
	{
		namespace material
		{
			std::vector<Material*> Material::s_materials;

			
			Material::Material(std::string name, Shader* shader)
			{
				m_materialName = name;
				m_shader = shader;
			}


			Material::~Material()
			{
			}

			Material* Material::CreateMaterial(aiMaterial * material)
			{
				Material* mat;
				std::string name = utils::AssimpLoader::GetMaterialName(material);

				for (unsigned int i = 0; i < s_materials.size(); i++)
				{
					if (s_materials[i]->GetName() == name)
						return s_materials[i];
				}

				int materialType = utils::AssimpLoader::GetMaterialShadingModel(material);
				switch (materialType)
				{
				case aiShadingMode_Phong:
				//	mat = new PhongMaterial(material);
					break;
				default:
					break;
				}

				if (mat)
					s_materials.push_back(mat);
				return mat;

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
