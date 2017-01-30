#include "GameObject.h"

namespace thomas
{
	namespace object
	{
		std::vector<GameObject*> GameObject::s_gameObjects;


		GameObject::GameObject(std::string name) : Object("GameObject",name)
		{
			m_transform = AddComponent<component::Transform>();
			s_gameObjects.push_back(this);
		}
		GameObject::~GameObject()
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				delete m_components[i];
			}
			m_components.empty();
		}
		GameObject * GameObject::Find(std::string name)
		{
			for (int i = 0; i < s_gameObjects.size(); i++)
			{
				if (s_gameObjects[i]->m_name == name)
					return s_gameObjects[i];
			}
			return NULL;
		}

		std::vector<GameObject*> GameObject::GetGameObjects()
		{
			return s_gameObjects;
		}
		

	}
}