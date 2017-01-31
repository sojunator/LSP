#pragma once

#include "../graphics/Model.h"
#include "../Common.h"
namespace thomas
{
	namespace utils
	{
		class THOMAS_API Plane
		{
		private:
			Plane();
			~Plane();

		public:
			static std::vector<thomas::graphics::Mesh* > CreatePlane(int size, int detail, std::string meshName, graphics::Material* mat);

		private:


		};
	}
}