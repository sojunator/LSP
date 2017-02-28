#include "GameObject.h"

namespace thomas
{
	namespace object
	{
		std::vector<GameObject*> GameObject::s_gameObjects;


		GameObject::GameObject(std::string name) : Object(name)
		{
		}
		GameObject::~GameObject()
		{
			for (unsigned int i = 0; i < this->m_components.size(); i++)
			{
				if (this->m_components[i])
				{
					Object::Destroy(this->m_components[i]);
				}
					
			}
			this->m_components.clear();

			for (unsigned int i = 0; i < s_gameObjects.size(); i++)
			{
				if (s_gameObjects[i] == this)
				{
					s_gameObjects.erase(s_gameObjects.begin() + i);
				
				}
			}

			Object::Destroy(this);
		}
		GameObject * GameObject::Find(std::string type)
		{
			for (unsigned int i = 0; i < s_gameObjects.size(); i++)
			{
				if (s_gameObjects[i]->m_type == type)
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

			for (unsigned int i = 0; i < gameObject->m_components.size(); i++)
			{
				if (gameObject->m_components[i])
				{
					Object::Destroy(gameObject->m_components[i]);
					
				}

			}
			gameObject->m_components.clear();

			for (unsigned int i = 0; i < s_gameObjects.size(); i++)
			{
				if (s_gameObjects[i] == gameObject)
				{
					s_gameObjects.erase(s_gameObjects.begin() + i);
					
				}
			}

			Object::Destroy(gameObject);

			return true;
		}


		void GameObject::SetActive(bool active)
		{
			m_active = active;
			for (component::Component* component : m_components)
			{
				component->SetActive(active && component->GetActive());
			}
			for (component::Transform* childTransforms : m_transform->m_children)
			{
				childTransforms->m_gameObject->SetActive(active && childTransforms->m_gameObject->GetActive());
			}
		}

		std::vector<GameObject*> GameObject::GetAllGameObjectsInScene(Scene* scene)
		{
			std::vector<GameObject*> output;
			for (GameObject* gameObject : s_gameObjects)
				if (gameObject->m_scene == scene)
					output.push_back(gameObject);
			return output;
		}
		

	}
}