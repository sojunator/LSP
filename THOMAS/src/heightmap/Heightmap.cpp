#include "Heightmap.h"

namespace thomas
{
	Heightmap::Heightmap(graphics::Material* mat, int size, int detail, std::string modelName) : m_detail(detail),
		m_size(size), 
		m_modelName(modelName)
	{
		m_mesh = &utils::Plane::CreatePlane(size, detail, modelName, mat);

	}

	Heightmap::~Heightmap()
	{
	}

}