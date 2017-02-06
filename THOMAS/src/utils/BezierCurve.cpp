#include "BezierCurve.h"

namespace thomas
{
	namespace utils
	{
		BezierCurve::BezierCurve()
		{

		}

		BezierCurve::~BezierCurve()
		{
		}

		

		math::Vector3 BezierCurve::GetBezierPoint(math::Vector3* points, float t, unsigned int nbrOfPoints)
		{
			if (nbrOfPoints == 1)
			{
				return points[0];
			}
			

			math::Vector3 point;

			return point;
		}
	}
}