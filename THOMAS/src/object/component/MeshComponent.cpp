#include "MeshComponent.h"

namespace thomas {
	namespace object {
		namespace component {



			MeshComponent::MeshComponent(GameObject * gameObject) : Component("MeshComponent", gameObject)
			{
				m_mesh = nullptr;
			}

			void MeshComponent::SetMesh(std::string name)
			{
				m_mesh = graphics::Mesh::GetMeshByName(name);

				if (!m_mesh)
					LOG("ERROR: no model named \"" << name  << "\" is loaded");
			}

			graphics::Mesh * MeshComponent::GetMesh()
			{
				return m_mesh;
			}

			graphics::MeshData * MeshComponent::GetMeshData()
			{
				if (m_mesh)
					return m_mesh->GetData();
				else
					return NULL;
			}

			std::string MeshComponent::GetName()
			{
				if (m_mesh)
					return m_mesh->GetName();
				else
					return std::string();
			}

			int MeshComponent::GetIndexCount()
			{
				if (m_mesh)
					return m_mesh->GetIndexCount();
				else
					return 0;
			}

			int MeshComponent::GetVertexCount()
			{
				if (m_mesh)
					return m_mesh->GetVertexCount();
				else
					return 0;
			}

			std::vector<graphics::Vertex>* MeshComponent::GetVertices()
			{
				if (m_mesh)
					return m_mesh->GetVertices();
				else
					return NULL;
			}

			std::vector<int>* MeshComponent::GetIndices()
			{
				if (m_mesh)
					return m_mesh->GetIndices();
				else
					return NULL;
			}


		}
	}
}