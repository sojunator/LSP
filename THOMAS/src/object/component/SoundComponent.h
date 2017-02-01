#pragma once

#include "Component.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class SoundComponent : public Component
			{
			public:
				SoundComponent(GameObject* gameObject);
				bool SetName(std::string name);
				std::string GetName();
				bool Play();
				void Pause();
				void Resume();
			private:
				std::string m_name;
			};
		}
	}
}