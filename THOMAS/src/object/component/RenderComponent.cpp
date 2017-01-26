#include "RenderComponent.h"

namespace thomas {
	namespace object {
		namespace component {

			RenderComponent::RenderComponent(GameObject * gameObject) : Component("ModelComponent", gameObject)
			{
			}

			void RenderComponent::SetModel(std::string name)
			{
				m_model = graphics::Model::GetModelByName(name);

				if (!m_model)
					LOG("ERROR: no model named \"" << name  << "\" is loaded");
			}

			graphics::Model * RenderComponent::GetModel()
			{
				return m_model;
			}

		}
	}
}