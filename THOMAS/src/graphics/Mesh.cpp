#include "Mesh.h"

namespace thomas {
	namespace graphics {
		std::vector <Mesh*> Mesh::s_meshes;

		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name)
		{
			m_vertices = vertices;
			m_indices = indices;
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
			vertexData.pSysMem = &m_vertices;
			vertexData.SysMemPitch = 0;
			vertexData.SysMemSlicePitch = 0;

			m_vertexBuffer = utils::D3d::CreateVertexBuffer(sizeof(m_vertices), false, false, &vertexData, ThomasCore::GetDevice());

			if (m_vertexBuffer == nullptr)
				LOG("ERROR::INITIALIZING::VERTEX::BUFFER");

			//Index buffer
			indexData.pSysMem = &m_indices;
			indexData.SysMemPitch = 0;
			indexData.SysMemSlicePitch = 0;

			m_indexBuffer = utils::D3d::CreateIndexBuffer(sizeof(m_indices), false, false, &indexData, ThomasCore::GetDevice());

			if (m_indexBuffer == nullptr)
				LOG("ERROR::INITIALIZING::INDEX::BUFFER");

			//Input layout
			/*D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			UINT numElements = ARRAYSIZE(layout);

			hr = ThomasCore::GetDevice()->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &m_inputLayout);

			if (FAILED(hr))
			{
				LOG("ERROR::FAILED TO CREATE INPUT LAYOUT");
				return;
			}
	
			ThomasCore::GetDeviceContext()->IASetInputLayout(m_inputLayout);
			ThomasCore::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);*/
		}
	}
}
