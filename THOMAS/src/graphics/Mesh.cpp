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
		}

		Mesh* Mesh::CreateMesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name)
		{
			Mesh *mesh = new Mesh(vertices, indices, name);
			s_meshes.push_back(mesh);
			return mesh;
		}

		bool Mesh::SetName(std::string name)
		{
			m_name = name;
			return false;
		}

		std::string Mesh::GetName()
		{
			return m_name;
		}

		void Mesh::SetupMesh()
		{
			//HRESULT
			HRESULT hr;

			//Blobs
			ID3D10Blob* VS_Buffer = nullptr;

			//Vertex buffer
			D3D11_SUBRESOURCE_DATA vertexData, indexData;
			vertexData.pSysMem = &m_data.vertices;
			vertexData.SysMemPitch = 0;
			vertexData.SysMemSlicePitch = 0;

			m_data.vertexBuffer = utils::D3d::CreateVertexBuffer(sizeof(m_data.vertices), false, false, &vertexData, ThomasCore::GetDevice());

			if (m_data.vertexBuffer == nullptr)
				LOG("ERROR::INITIALIZING::VERTEX::BUFFER");

			//Index buffer
			indexData.pSysMem = &m_data.indices;
			indexData.SysMemPitch = 0;
			indexData.SysMemSlicePitch = 0;

			m_data.indexBuffer = utils::D3d::CreateIndexBuffer(sizeof(m_data.indices), false, false, &indexData, ThomasCore::GetDevice());

			if (m_data.indexBuffer == nullptr)
				LOG("ERROR::INITIALIZING::INDEX::BUFFER");

		}
	}
}
