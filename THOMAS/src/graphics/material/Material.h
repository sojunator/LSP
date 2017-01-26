#pragma once
#include "../Shader.h"
#include "../Texture.h"
#include "../../utils/AssimpLoader.h"

namespace thomas
{
	namespace graphics
	{
		namespace material
		{
			class Material
			{
			private:
				
			public:
				Material(std::string name, Shader* shader);

				static Material* CreateMaterial(aiMaterial* material);
				static Material* GetMaterialByName(std::string name);
				static std::vector<Material*> GetLoadedMaterials();
				static std::vector<Material*> GetMaterialsByShaders(Shader* shader);
				static std::vector<Material*> GetMaterialsByShaders(std::string name);
				bool Bind();
				bool Unbind();
				std::string GetName();
				Shader* GetShader();
				
				~Material();

			private:
				static std::vector<Material*> s_materials;

			protected:
				Shader* m_shader;
				std::string m_materialName;
				ID3D11Buffer* m_materialPropertiesBuffer;
				std::vector<Texture*> m_textures;
			};
		}
	}
}

