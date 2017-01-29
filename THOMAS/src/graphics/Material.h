#pragma once
#include <map>
#include "Shader.h"
#include "Texture.h"
#include "../utils/AssimpLoader.h"

namespace thomas
{
	namespace graphics
	{
		class Material
		{
		private:
			virtual Material* CreateInstance(std::string dir, std::string name, aiMaterial* assimpMaterial) { return NULL; }
		public:
			Material(Shader* shader);
			Material(std::string shader);
			Material(std::string name, Shader* shader);

			static Material* CreateMaterial(Material* material);
			static Material* CreateMaterial(std::string dir, std::string materialType, aiMaterial* assimpMaterial);
			static bool RegisterNewMaterialType(std::string type, Material* material);

			static Material* GetMaterialByName(std::string name);

			static std::vector<Material*> GetLoadedMaterials();
			static std::vector<Material*> GetMaterialsByShader(Shader* shader);
			static std::vector<Material*> GetMaterialsByShader(std::string name);


			bool Bind();
			bool Unbind();

			std::string GetName();
			Shader* GetShader();

			~Material();

		private:

			static std::vector<Material*> s_materials;
			static std::map<std::string, Material*> s_materialTypes;

		protected:
			Shader* m_shader;
			std::string m_materialName;
			ID3D11Buffer* m_materialPropertiesBuffer;
			std::vector<Texture*> m_textures;
		};
	}
}

