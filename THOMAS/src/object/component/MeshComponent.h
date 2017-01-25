#pragma once
#include "Component.h"
#include "../../graphics/Mesh.h"
namespace thomas
{
	namespace object
	{
		namespace component
		{
			class THOMAS_API MeshComponent : public Component
			{
			private:
			public:

				MeshComponent(GameObject* gameObject);

				void SetMesh(std::string name);
				graphics::Mesh* GetMesh();

				graphics::MeshData* GetMeshData();

			private:
				graphics::Mesh* m_mesh;
			};
		}
	}
}