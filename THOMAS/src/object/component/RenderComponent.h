#pragma once
#include "Component.h"
#include "../../graphics/Model.h"
namespace thomas
{
	namespace object
	{
		namespace component
		{
			class THOMAS_API RenderComponent : public Component
			{
			private:
			public:
				RenderComponent();
				void SetModel(std::string name);
				graphics::Model * GetModel();
				void Update();
			private:
				graphics::Model* m_model;
			};
		}
	}
}