#include "GameObject.h"

namespace thomas
{
	namespace object
	{
		std::vector<GameObject*> GameObject::s_gameObjects;

		GameObject::GameObject(std::string name) : Object(name)
		{
			m_transform = AddComponent<component::Transform>();
			Instantiate(this);
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
		template<typename T>
		T* GameObject::AddComponent()
		{
			if (std::is_base_of<component::Component, T>::value)
			{
				T* component = new T();
				m_components.push_back(component);
				return component;
			}
			return NULL;
		}
		template<typename T>
		T* GameObject::GetComponent()
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				if (typeid(T) == typeid(m_components[i]));
			}
		}

	}
}