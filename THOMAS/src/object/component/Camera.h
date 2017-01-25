#pragma once
#include "Component.h"
#include "../../utils/Math.h"

/**
*Camera class
*/
namespace thomas
{
	namespace object
	{
		namespace component
		{
			class THOMAS_API Camera : public Component
			{
			private:
				void UpdateProjMatrix();

			public:
				Camera(GameObject* gameObject);
				math::Matrix GetProjMatrix();
				math::Matrix GetViewProjMatrix();

				float GetFov();
				void SetFov(float fov);

				float GetNear();
				void SetNear(float viewNear);

				float GetFar();
				void SetFar(float viewFar);

				float GetAspectRatio();
				void SetAspectRatio(float aspectRatio);
				
			private:
				math::Matrix m_projMatrix;
				float m_fov;
				float m_near;
				float m_far;
				float m_aspectRatio;
			};
		}
	}
}