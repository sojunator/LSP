#include "Materials.h"
#include "../../utils/AssimpLoader.h"
namespace thomas
{
	namespace graphics
	{
		namespace material
		{
			std::vector<Material*> Material::s_materials;

			
			Material::Material(std::string dir, std::string name, Shader* shader, aiMaterial* material)
			{
				m_materialName = name;
				m_shader = shader;

				m_textures = utils::AssimpLoader::GetMaterialTextures(material, dir);


			}


			Material::~Material()
			{
				m_materialPropertiesBuffer->Release();
			}

			Material* Material::CreateMaterial(std::string dir, aiMaterial * material)
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
					mat = new PhongMaterial(dir, name, material);
					break;
				default:
					mat = new PhongMaterial(dir, name, material);
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

			std::vector<Material*> Material::GetMaterialsByShader(Shader * shader)
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

			std::vector<Material*> Material::GetMaterialsByShader(std::string name)
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

			bool Material::Bind()
			{

				bool buffer = m_shader->BindBuffer(m_materialPropertiesBuffer, Shader::ResourceType::MATERIAL);
				bool texture = true;
				for (unsigned int i = 0; i < m_textures.size(); i++)
				{
					if(texture)
						texture = m_textures[i]->Bind();
				}
				return buffer && texture;
			}

			bool Material::Unbind()
			{
				bool buffer = m_shader->BindBuffer(NULL, Shader::ResourceType::MATERIAL);
				bool texture = true;
				for (unsigned int i = 0; i < m_textures.size(); i++)
				{
					if (texture)
						texture = m_textures[i]->Unbind();
				}
				return buffer && texture;
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
