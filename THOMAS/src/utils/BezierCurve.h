#pragma once
#include "../Common.h"

#include "Math.h"
#include <string>
#include <vector>


namespace thomas
{
	namespace utils
	{
		class THOMAS_API BezierCurve
		{
		public:
			BezierCurve();
			~BezierCurve();

			math::Vector3 GetBezierPoint(math::Vector3* points, float t, unsigned int nbrOfPoints);
		private:

		};

	}
}