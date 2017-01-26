#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Math.h"
#include "../../include/assimp/Importer.hpp"
#include "../../include/assimp/scene.h"
#include "../../include/assimp/postprocess.h"

namespace thomas
{
	namespace graphics 
	{
		class Mesh;
		class Model;
	}
	namespace utils
	{

		class AssimpLoader
		{
		private:
			static graphics::Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string meshName);
			static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<graphics::Mesh*> &meshes);
			static void ProcessMaterials(aiScene* scene);
		public:
			static graphics::Model* LoadModel(std::string name, std::string path);
			
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

