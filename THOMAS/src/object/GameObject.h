#pragma once
#include "component\Components.h"
#include "Object.h"
#include <vector>
namespace thomas
{
	class Scene;
	namespace object
	{
		class THOMAS_API GameObject : public Object
		{
		private:
		public:
			component::Transform* m_transform;

			GameObject(std::string name);
			~GameObject();
			template<typename T>
			T* AddComponent();
			template<typename T>
			T* GetComponent();
			template<typename T>
			std::vector<T*> GetComponents();

			static GameObject* Find(std::string name);

			template<typename T>
			static std::vector<GameObject*> FindGameObjectsWithComponent();
			static std::vector<GameObject*> GetGameObjects();

			static bool Destroy(GameObject *object);

			static GameObject* Instantiate(GameObject* gameObject, Scene* scene);
			static GameObject* Instantiate(GameObject* gameObject, component::Transform* parent, Scene* scene);
			static GameObject* Instantiate(GameObject* gameObject, math::Vector3 position, math::Quaternion rotation, Scene* scene);
			static GameObject* Instantiate(GameObject* gameObject, math::Vector3 position, math::Quaternion rotation, component::Transform* parent, Scene* scene);

			virtual bool Start() { return true; }
			virtual void Update() {}
			virtual void FixedUpdate() {}
			virtual void Render() {}

			static std::vector<GameObject*> GetAllGameObjectsInScene(Scene* scene);

		private:		
			static std::vector<GameObject*> s_gameObjects;
		protected:
			bool m_active;
			std::vector<component::Component*> m_components;
			
		};

		template<typename T>
		T* GameObject::AddComponent()
		{
			if (std::is_base_of<component::Component, T>::value)
			{
				T* component = new T(this);
				Object::Instantiate(component, m_scene);
				m_components.push_back(component);
				return component;
			}
			LOG("Invalid component");
			return NULL;
		}
		template<typename T>
		T* GameObject::GetComponent()
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				T* comp = dynamic_cast<T*>(m_components[i]);
				if (comp)
					return comp;
			}
			return NULL;
		}

		template<typename T>
		inline std::vector<T*> GameObject::GetComponents()
		{
			std::vector<T*> components;
			for (int i = 0; i < m_components.size(); i++)
			{
				T* comp = dynamic_cast<T*>(m_components[i]);
				if (comp)
					components.push_back(comp);
			}
			return components;
		}

		template<typename T>
		inline std::vector<GameObject*> GameObject::FindGameObjectsWithComponent()
		{
			std::vector<GameObject*> gameObjectsWithComponent;
			for (int i = 0; i < s_gameObjects.size(); i++)
			{
				T* component = s_gameObjects[i]->GetComponent<T>();
				if (component)
					gameObjectsWithComponent.push_back(s_gameObjects[i]);
			}
			return gameObjectsWithComponent;
		}


	}
}