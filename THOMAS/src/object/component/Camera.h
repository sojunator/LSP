#pragma once
#include "Component.h"
#include "../../utils/Math.h"
#include "../../graphics/Skybox.h"
#include "../../graphics/Bitmap.h"
#include "../../graphics/TextRender.h"
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
				math::Matrix GetViewMatrix();
				math::Matrix GetProjMatrix();
				math::Matrix GetViewProjMatrix();
				math::Vector3 GetPosition();

				float GetFov();
				void SetFov(float fov);

				float GetNear();
				void SetNear(float viewNear);

				float GetFar();
				void SetFar(float viewFar);

				math::Viewport GetViewport();
				void SetViewport(math::Viewport viewport);
				void SetViewport(float x, float y, float width, float height);

				float GetAspectRatio();

				void SetSkybox(std::string path, std::string shaderName);

				void BindSkybox();
				void UnbindSkybox();

				void SetGUI(std::string path, std::string shaderName, int, int);

				void BindGUI();
				void UnbindGUI();

				void ReleaseGUI();
				void ReleaseSkybox();

				//Text
				void SetTextFont(std::string font);
				void OutputText(std::string output, float posX, float posY, float scale, float rotation,
								math::Vector3 color, bool dropShadow, bool outline);
				void ReleaseText();
				
			private:
				math::Matrix m_projMatrix;
				float m_fov;
				float m_near;
				float m_far;
				math::Viewport m_viewport;
				graphics::Skybox* m_skybox;
				graphics::Bitmap* m_bitmap;

			};
		}
	}
}