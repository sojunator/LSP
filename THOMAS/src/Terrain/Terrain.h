#pragma once
#include "../Common.h"
#include "../Thomas.h"

namespace thomas
{
	class THOMAS_API Terrain
	{
	private:
		std::vector<thomas::graphics::Mesh*> m_mesh;
		int m_detail;
		int m_size;
		std::string m_modelName;

	public:
		Terrain(graphics::Material* mat, int size = 256, int detail = 1, std::string modelName = "Plane-1");
	private:
		~Terrain();
	};
}