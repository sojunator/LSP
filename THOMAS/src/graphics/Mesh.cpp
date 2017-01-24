#include "Mesh.h"

namespace thomas {
	namespace graphics {
		std::vector <Mesh*> Mesh::s_meshes;

		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::string name)
		{
			m_vertices = vertices;
			m_indices = indices;
			m_name = name;
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
	}
}
