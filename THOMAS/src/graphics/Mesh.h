#pragma once
#include "../Common.h"
#include <d3d11.h>
#include "../utils/Math.h"
#include <vector>
#include "../../include/assimp/Importer.hpp"
#include "../../include/assimp/scene.h"
#include "../../include/assimp/postprocess.h"
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

		struct MeshData
		{
			std::vector<Vertex> vertices;
			std::vector<int> indices;
			ID3D11Buffer* vertexBuffer;
			ID3D11Buffer* indexBuffer;
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
			static std::vector<Mesh*> s_meshes;
			std::string m_name;
			MeshData m_data;

		};
	}
}

