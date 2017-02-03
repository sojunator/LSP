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
				RenderComponent(GameObject* gameObject);
				void SetModel(std::string name);
				graphics::Model * GetModel();
			private:
				graphics::Model* m_model;
			};
		}
	}
}