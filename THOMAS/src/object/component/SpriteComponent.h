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
			};
		}
	}
}

