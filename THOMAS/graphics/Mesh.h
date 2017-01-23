#pragma once
#include "../Common.h"
#include <d3d11.h>
#include "../utils/Math.h"
#include <vector>
#include "../assimpincludes/assimp/Importer.hpp"
#include "../assimpincludes/assimp/scene.h"
#include "../assimpincludes/assimp/postprocess.h"

namespace thomas 
{
	namespace graphics 
	{
		struct Vertex 
		{
			math::Vector3 position;
			math::Vector2 uv;
			math::Vector3 normal;
		};

		class THOMAS_API Mesh
		{
		private:
		public:
			Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name);
			~Mesh();

			bool SetName(std::string name);
	
			std::string GetName();

		private:
			std::vector<Vertex> m_vertices;
			std::vector<int> m_indices;
			static std::vector<Mesh*> s_meshes;
			std::string m_name;

		};
	}
}

