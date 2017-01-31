#include "Material.h"
#include "../utils/AssimpLoader.h"
namespace thomas
{
	namespace graphics
	{

		std::vector<Material*> Material::s_materials;
		std::map<std::string, Material*> Material::s_materialTypes;

		Material::Material(Shader * shader)
		{
			m_shader = shader;
		}

		Material::Material(std::string shader)
		{
			m_shader = Shader::GetShaderByName(shader);
			if (!m_shader)
				LOG("Failed to create material with shader: " << shader);
		}

		Material::Material(std::string name, Shader* shader)
		{
			m_materialName = name;
			m_shader = shader;

		}


		Material::~Material()
		{
			if(m_materialPropertiesBuffer)
				m_materialPropertiesBuffer->Release();
		}

		Material * Material::CreateMaterial(Material * material)
		{
			for (unsigned int i = 0; i < s_materials.size(); i++)
			{
				if (s_materials[i]->GetName() == material->GetName())
					return s_materials[i];
			}
			s_materials.push_back(material);
			return material;
		}

		Material * Material::CreateMaterial(std::string dir, std::string materialType, aiMaterial * assimpMaterial)
		{
			std::string name = utils::AssimpLoader::GetMaterialName(assimpMaterial);

			for (unsigned int i = 0; i < s_materials.size(); i++)
			{
				if (s_materials[i]->GetName() == name)
					return s_materials[i];
			}


			Material* instancedMaterial;
			if (s_materialTypes.find(materialType) != s_materialTypes.end()) //Material was found. So now we create a new copy of it.
			{
				Material* matTemplate = s_materialTypes.find(materialType)->second;
				instancedMaterial = matTemplate->CreateInstance(dir, name, assimpMaterial);
				s_materials.push_back(instancedMaterial);
				return instancedMaterial;
			}
			
			LOG("No material of type: " << materialType << " exists.");
			return NULL;

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

		bool Material::RegisterNewMaterialType(std::string type, Material * material)
		{
			if (s_materialTypes.find(type) == s_materialTypes.end()) //Material is not already registered.
			{
				s_materialTypes[type] = material;
				return true;
			}
			return false;
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

		void Material::Destroy()
		{
			for (unsigned int i = 0; i < s_materials.size(); i++)
			{
				delete s_materials[i];
			}
			for (auto const& materialType : s_materialTypes)
			{
				delete materialType.second;
			}
		}

		bool Material::Bind()
		{

			bool buffer = m_shader->BindBuffer(m_materialPropertiesBuffer, Shader::ResourceType::MATERIAL);
			bool texture = true;
			for (unsigned int i = 0; i < m_textures.size(); i++)
			{
				if (texture)
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
