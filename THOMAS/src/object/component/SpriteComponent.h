#pragma once
#include "Component.h"
#include "../../utils/Math.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class SpriteComponent : public Component
			{
			public:
				SpriteComponent();
				math::Vector2 GetPosition();
				float GetScale();
				UINT GetWidth();
				UINT GetHeight();
				std::string GetSignature();

				void SetName(std::string name);
				void SetPositionX(float posX);
				void SetPositionY(float posY);
				void SetScale(float scale);
				
			private:
				math::Vector2 m_imagePos;
				std::string m_name;
				float m_scale;	
			};
		}
	}
}

