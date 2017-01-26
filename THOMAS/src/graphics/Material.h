#pragma once
#include "Shader.h"
#include "../../include/assimp/Importer.hpp"
#include "../../include/assimp/scene.h"
#include "../../include/assimp/postprocess.h"

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
				static Material* CreateMaterial(aiMaterial* material);
				static Material* GetMaterialByName(std::string name);
				static std::vector<Material*> GetLoadedMaterials();
				static std::vector<Material*> GetMaterialsByShaders(Shader* shader);
				static std::vector<Material*> GetMaterialsByShaders(std::string name);
				virtual bool BindMaterial() = 0;
				virtual bool UnbindMaterial() = 0;
				std::string GetName();
				Shader* GetShader();
				Material();
				~Material();

			private:
				static std::vector<Material*> s_materials;

			protected:
				Shader* m_shader;
				std::string m_materialName;
				

			};
		}
	}
}

