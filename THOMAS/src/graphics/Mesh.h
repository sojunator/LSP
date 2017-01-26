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

		/*struct Texture {
			int id;
			std::string type;
			aiString path;
		};*/

		struct MeshData
		{
			std::vector<Vertex> vertices;
			//std::vector<Texture> textures;
			std::vector<int> indices;
			ID3D11Buffer* vertexBuffer;
			ID3D11Buffer* indexBuffer;
		};

		class THOMAS_API Mesh
		{
		private:
			void SetupMesh();
			Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name);
		public:
			~Mesh();
			static Mesh* CreateMesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name);

			bool SetName(std::string name);

			MeshData* GetData();
	
			std::string GetName();

			int GetIndexCount();
			int GetVertexCount();
			
			std::vector<Vertex>* GetVertices();
			std::vector<int>* GetIndices();

			static Mesh* GetMeshByName(std::string name);
			static std::vector<Mesh*> GetLoadedMeshes();

		private:
			static std::vector<Mesh*> s_meshes;
			std::string m_name;
			MeshData m_data;

		};
	}
}

