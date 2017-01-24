#pragma once
#include "Common.h"
#include "../utils/Math.h"
/**
*Camera class
*/
namespace thomas
{
	class THOMAS_API Camera
	{
	private:
		void CreateViewMatrix(math::Vector3 camPos, math::Vector3 focusAt);
		void CreateProjMatrix(float fov, float nearPlane, float farPlane);
		void CreateViewProjMatrix();
		void Update();
		
	public:
		Camera(math::Vector3 camPos, math::Vector3 focusAt, float fov, float nearPlane, float farPlane);
		void MoveCamera(math::Vector3 direction);	///Send 1 or 0 in x,y,z to move or not to move
		void RotateCamera(math::Vector3 rotate);	///Rotate in radians
		math::Matrix GetViewMatrix();
		math::Matrix GetProjMatrix();
		math::Matrix GetViewProjMatrix();
		math::Vector3 GetCamPos();
		math::Vector3 GetCamDirection();
		math::Vector3 GetFocus();
		float GetFov();
		float GetNear();
		float GetFar();
		void SetCamPos(math::Vector3 camPos);
		void SetCamDirection(math::Vector3 camDir);
		void SetFocus(math::Vector3 focusAt);	///Focusing on this point
		void SetFov(float fov);
		void SetNear(float viewNear);
		void SetFar(float viewFar);

	private:
		math::Matrix m_viewMatrix;
		math::Matrix m_projMatrix;
		math::Matrix m_viewProjMatrix;
		math::Vector3 m_camPos;
		math::Vector3 m_camDir;
		math::Vector3 m_focusAt;
		float m_fov;
		float m_near;
		float m_far;
	};
}