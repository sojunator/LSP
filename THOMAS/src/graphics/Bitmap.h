#pragma once
#include "../utils/Math.h"
#include "Shader.h"

namespace thomas
{
	namespace graphics
	{
		class Bitmap
		{
		private:

		public:
			Bitmap();
			~Bitmap();

		private:
			int m_screenWidth, m_screenHeight;
			int m_bitmapWidth, m_bitmapHeight;
			int m_previousPosX, m_previousPosY;
		};
	}
}

