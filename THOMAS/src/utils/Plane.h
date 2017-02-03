#pragma once

#include "../graphics/Model.h"
#include "../Common.h"
#include "noise\noise.h"


namespace thomas
{
	namespace utils
	{

		class THOMAS_API Plane
		{
		public:
			struct PlaneData
			{
				std::vector<graphics::Vertex> verts;
				std::vector<int> indices;
			};

		private:
			Plane();
			~Plane();

		public:


			static PlaneData Plane::CreatePlane(int size, float detail, std::string meshName,
				graphics::Material* mat);

		private:
		};
	}
}