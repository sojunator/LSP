#pragma once
#include <iostream>
#include "../graphics/Mesh.h"

namespace thomas
{
	namespace utils
	{
		struct Model
		{
			std::vector<graphics::Mesh*> meshes;
		};

		class AssimpLoader
		{
		private:
			static graphics::Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string nodeName);
			static void ProcessNode(aiNode* node, const aiScene* scene, Model &model);

		public:
			static Model LoadModel(std::string path);

			static std::string GetMaterialName(aiMaterial* material);
			static int GetMaterialShadingModel(aiMaterial* material);
			static math::Color GetMaterialColor(aiMaterial* material, const char* pKey, unsigned int type, unsigned int idx);
			static float GetMaterialShininess(aiMaterial* material);
			static float GetMaterialShininessStrength(aiMaterial* material);
			static int GetMaterialBlendMode(aiMaterial* material);
			static float getMaterialOpacity(aiMaterial* material);


		private:
			
		};

	}
}

