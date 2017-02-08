#pragma once
#include "../../Common.h"
#include "../Object.h"

namespace thomas
{
	namespace object
	{
		class GameObject;

		namespace component
		{
			class THOMAS_API Component : public Object
			{
			private:
			public:
				Component(std::string name, GameObject* gameObject);
				GameObject* GetGameObject();
			private:
			protected:
				GameObject* m_gameObject;
			};
		}
	}
}