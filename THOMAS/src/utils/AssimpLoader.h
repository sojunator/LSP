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
			static graphics::Mesh* ProcessMesh(aiMesh* mesh, std::string nodeName);
			static void ProcessNode(aiNode* node, const aiScene* scene, Model &model);

		public:
			static Model LoadModel(std::string path);
			
		private:
			
		};

	}
}

