#include "GameObject.h"

namespace thomas
{
	namespace object
	{
		std::vector<GameObject*> GameObject::s_gameObjects;


		GameObject::GameObject(std::string name) : Object("GameObject",name)
		{
			m_transform = AddComponent<component::Transform>();
		}
		GameObject::~GameObject()
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				if(m_components[i])
					Object::Destroy(m_components[i]);
			}
			m_components.empty();

			for (int i = 0; i < s_gameObjects.size(); i++)
			{
				if (s_gameObjects[i] == this)
				{
					s_gameObjects.erase(s_gameObjects.begin() + i);
				}
			}

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

		bool GameObject::Destroy(GameObject * gameObject)
		{
			delete gameObject;
			return true;
		}

		GameObject* GameObject::Instantiate(GameObject * gameObject)
		{
			Object::Instantiate(gameObject);
			s_gameObjects.push_back(gameObject);
			return gameObject;
		}

		GameObject* GameObject::Instantiate(GameObject * gameObject, component::Transform * parent)
		{
			gameObject->m_transform->m_parent = parent;
			return Instantiate(gameObject);
		}

		GameObject* GameObject::Instantiate(GameObject * gameObject, math::Vector3 position, math::Quaternion rotation)
		{
			gameObject->m_transform->SetPosition(position);
			gameObject->m_transform->SetRotation(rotation);
			return Instantiate(gameObject);
		}

		GameObject* GameObject::Instantiate(GameObject * gameObject, math::Vector3 position, math::Quaternion rotation, component::Transform * parent)
		{
			gameObject->m_transform->SetPosition(position);
			gameObject->m_transform->SetRotation(rotation);
			return Instantiate(gameObject, parent);
		}
		

	}
}