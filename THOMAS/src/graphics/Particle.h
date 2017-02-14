#pragma once
#include "..\ThomasCore.h"

namespace thomas
{
	namespace graphics
	{
		class Material;
		class THOMAS_API Particle
		{
		public:
			bool Bind();
			bool Unbind();
		private:
			std::string m_name;
			math::Vector3 m_position;
			Material* m_materal
		};
	}
}