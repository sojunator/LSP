#include "Plane.h"
#include <time.h>

namespace thomas
{
	namespace utils
	{
		std::vector<thomas::graphics::Mesh*> Plane::CreatePlane(int size, float detail, std::string meshName,
			graphics::Material* mat)
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
			for (int j = 0; j < size * detail; j++)
			{
				for (int i = 0; i < size * detail; i++)
				{
					temp_vert.position.x = (float)j / detail;
					temp_vert.position.y = 0.0f;
					temp_vert.position.z = -(float)i / detail;
					temp_vert.uv.x = j / ((float)size * detail);
					temp_vert.uv.y = 1-(i - (float)size * detail) / ((float)size * detail);
					verts.push_back(temp_vert);
				}
			}

			// triangulate points
			for (int i = 0; i < (size * detail) - 1; i++)
			{
				int index = size*detail * (i + 1);
				for (int j = 0; j < (size * detail) - 1; j++)
				{
					
					indices.push_back(j + i * size*detail);
					indices.push_back(index);
					indices.push_back(index + 1);

					indices.push_back(j + i * size*detail);
					indices.push_back(index + 1);
					indices.push_back((j + i * size*detail) + 1);

					index++;
				}
			}

			std::vector<thomas::graphics::Mesh*> mesh;
			graphics::Mesh* m = new graphics::Mesh(verts, indices, meshName, mat);
			mesh.push_back(m);
			return mesh;
		}
	}
}
