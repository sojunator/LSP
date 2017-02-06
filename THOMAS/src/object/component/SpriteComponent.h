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
				SpriteComponent(GameObject* gameObject);
				math::Vector2 GetPosition();
				float GetScale();

				void SetPositionX(float posX);
				void SetPositionY(float posY);
				void SetScale(float scale);
				
			private:
				math::Vector2 m_imagePos;			
				float m_scale;	
			};
		}
	}
}

