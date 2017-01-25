#include "Component.h"
#include "../GameObject.h"
namespace thomas
{
	namespace object
	{
		namespace component
		{

			Component::Component(std::string name, GameObject * gameObject) : Object("Component", gameObject->GetName() + ":" + name)
			{
				m_gameObject = gameObject;
			}

			GameObject * Component::GetGameObject()
			{
				return nullptr;
			}

		}
	}
}