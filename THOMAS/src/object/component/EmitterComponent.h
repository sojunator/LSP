#pragma once
#include "Component.h"
#include "..\..\utils\math.h"
#include "..\..\graphics\Texture.h"
#include "..\..\graphics\Shader.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class EmitterComponent : public Component
			{
			public:
				void Play(float frequency);
				void Stop();
			private:
				graphics::Texture* m_texture;
				std::string m_name;
				math::Vector3 m_position;
			};
		}
	}
}