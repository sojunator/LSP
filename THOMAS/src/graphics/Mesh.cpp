#include "Mesh.h"

namespace thomas {
	namespace graphics {
		std::vector <Mesh*> Mesh::s_meshes;

		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name)
		{
			
			m_data.vertices = vertices;
			m_data.indices = indices;
			m_name = name;
			SetupMesh();
		}

		Mesh::~Mesh()
		{
			m_data.vertexBuffer->Release();
			m_data.indexBuffer->Release();
		}

		Mesh* Mesh::CreateMesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name)
		{
			Mesh *mesh = new Mesh(vertices, indices, name);
			if(mesh)
				s_meshes.push_back(mesh);
			return mesh;
		}

		bool Mesh::SetName(std::string name)
		{
			m_name = name;
			return false;
		}

		MeshData* Mesh::GetData()
		{
			return &m_data;
		}

		std::string Mesh::GetName()
		{
			return m_name;
		}

		int Mesh::GetIndexCount()
		{
			return m_data.indices.size();
		}

		int Mesh::GetVertexCount()
		{
			return m_data.vertices.size();
		}

		std::vector<Vertex>* Mesh::GetVertices()
		{
			return &m_data.vertices;
		}

		std::vector<int>* Mesh::GetIndices()
		{
			return &m_data.indices;
		}

		Mesh * Mesh::GetMeshByName(std::string name)
		{
			for (int i = 0; i < s_meshes.size(); i++) {
				if (s_meshes[i]->GetName() == name)
					return s_meshes[i];
			}
			return NULL;
		}

		std::vector<Mesh*> Mesh::GetLoadedMeshes()
		{
			return s_meshes;
		}

		void Mesh::SetupMesh()
		{
			//HRESULT
			HRESULT hr;


			m_data.vertexBuffer = utils::D3d::CreateBufferFromVector(m_data.vertices, D3D11_BIND_VERTEX_BUFFER);

			if (m_data.vertexBuffer == nullptr)
				LOG("ERROR::INITIALIZING::VERTEX::BUFFER");


			m_data.indexBuffer = utils::D3d::CreateBufferFromVector(m_data.indices, D3D11_BIND_INDEX_BUFFER);

			if (m_data.indexBuffer == nullptr)
				LOG("ERROR::INITIALIZING::INDEX::BUFFER");

		}
	}
}
