#pragma once
#include "Component.h"
#include "..\..\utils\math.h"
#include "..\..\graphics\Texture.h"
#include "..\..\graphics\Shader.h"
#include "..\..\graphics\ParticleSystem.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class EmitterComponent : public Component
			{
			public:
				void Emit();
				void Stop();
			private:
				graphics::Texture* m_texture;
				std::string m_name;
				math::Vector3 m_position;
				bool m_isEmitting;
				unsigned int m_nrOfParticles;
			};
		}
	}
}
