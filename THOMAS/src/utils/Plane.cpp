#include "Plane.h"

namespace thomas
{
	namespace utils
	{
		void Plane::CreatePlane(int size)
		{
			std::vector<graphics::Vertex> verts;
			std::vector<int> indices;
			float x, y, z;
			graphics::Vertex temp_vert;
			
			// Defualt temp values, must be calulated later
			temp_vert.uv.x = 0.0f;
			temp_vert.uv.y = 0.0f;
			temp_vert.normal.x = 0.0f;
			temp_vert.normal.y = 1.0f;
			temp_vert.normal.z = 0.0f;

			// Create points
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					temp_vert.position.x = (float)j;
					temp_vert.position.y = (float)i;
					temp_vert.position.z = 0.0f;
					verts.push_back(temp_vert);
				}
			}

			// triangulate points
			for (int i = 0; i < size - 1; i++)
			{
				for (int j = 0; j < size - 1; j++)
				{
					indices.push_back(j);
					indices.push_back(size * (i + 1));
					indices.push_back(size * (i + 1) + 1);

					indices.push_back(j);
					indices.push_back(size * (i + 1) + 1);
					indices.push_back(j + 1);

				}
			}

			std::vector<thomas::graphics::Mesh* > mesh;
			mesh.push_back(&graphics::Mesh(verts, indices, "Plane-1", NULL));
			graphics::Model::CreateModel("Plane-1", mesh);
		}
	}
}
