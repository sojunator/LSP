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
			

		}
		GameObject * GameObject::Find(std::string type)
		{
			for (int i = 0; i < s_gameObjects.size(); i++)
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

			for (int i = 0; i < gameObject->m_components.size(); i++)
			{
				if (gameObject->m_components[i])
					Object::Destroy(gameObject->m_components[i]);
			}
			gameObject->m_components.empty();

			for (int i = 0; i < s_gameObjects.size(); i++)
			{
				if (s_gameObjects[i] == gameObject)
				{
					s_gameObjects.erase(s_gameObjects.begin() + i);
				}
			}

			Object::Destroy(gameObject);

			return true;
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