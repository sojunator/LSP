#include "MeshComponent.h"


namespace thomas {
	namespace object {
		namespace component {



			MeshComponent::MeshComponent(GameObject * gameObject) : Component("MeshComponent", gameObject);
			{
			}

			void MeshComponent::SetMesh(std::string name)
			{
				m_mesh = graphics::Mesh::GetMeshByName(name);
			}

			graphics::Mesh * MeshComponent::GetMesh()
			{
				return m_mesh;
			}

			graphics::MeshData * MeshComponent::GetMeshData()
			{
				return m_mesh->GetData();
			}


		}
	}
}