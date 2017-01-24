#pragma once
#include "../Common.h"
#include <d3d11.h>
#include "../utils/Math.h"
#include <vector>
#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"
#include "../utils/d3d.h"
#include "../ThomasCore.h"

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
			void SetupMesh();
		public:
			Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name);
			~Mesh();
			static Mesh* CreateMesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name);

			bool SetName(std::string name);
	
			std::string GetName();

		private:
			std::vector<Vertex> m_vertices;
			std::vector<int> m_indices;
			static std::vector<Mesh*> s_meshes;
			std::string m_name;
			ID3D11Buffer* m_vertexBuffer;
			ID3D11Buffer* m_indexBuffer;
			ID3D11InputLayout* m_inputLayout;

		};
	}
}

