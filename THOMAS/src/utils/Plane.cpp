#include "Plane.h"
#include <time.h>

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
			srand(time(NULL));
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
					temp_vert.position.y = 0.0f;
					temp_vert.position.z = (float)i;
					verts.push_back(temp_vert);
				}
			}

			// triangulate points
			for (int i = 0; i < size - 1; i++)
			{
				int index = size * (i + 1);
				for (int j = 0; j < size - 1; j++)
				{
					
					indices.push_back(j + i * size);
					indices.push_back(index);
					indices.push_back(index + 1);

					indices.push_back(j + i * size);
					indices.push_back(index + 1);
					indices.push_back((j + i * size) + 1);

					index++;
				}
			}

			std::vector<thomas::graphics::Mesh* > mesh;
			graphics::Mesh* m = new graphics::Mesh(verts, indices, "Plane-1", NULL);
			mesh.push_back(m);
			graphics::Model::CreateModel("Plane-1", mesh);
		}
	}
}
