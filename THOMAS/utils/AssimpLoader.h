#pragma once
#include <iostream>
#include "../graphics/Mesh.h"

namespace thomas
{
	namespace utils
	{
		class AssimpLoader
		{
		private:
			static graphics::Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
			static void ProcessNode(aiNode* node, const aiScene* scene);

		public:
			static void LoadModel(std::string path);
			
		private:
			struct Model
			{
				std::vector<graphics::Mesh*> meshes;
			};
		};
	}
}

