#pragma once
#include "Mesh.h"
#include <iostream>

namespace thomas
{
	namespace graphics
	{
		class AssimpLoader
		{
		private:
			static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
			static void ProcessNode(aiNode* node, const aiScene* scene);

		public:
			AssimpLoader();
			~AssimpLoader();
			static void LoadModel(std::string path);

		private:
			struct Model
			{
				std::vector<Mesh*> meshes;
			};


		};
	}
}

