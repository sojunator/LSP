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

			GameObject(std::string type);
			~GameObject();
			template<typename T>
			T* AddComponent();
			template<typename T>
			T* GetComponent();
			template<typename T>
			std::vector<T*> GetComponents();

			static GameObject* Find(std::string type);
			static std::vector<GameObject*> FindAllOfType(std::string type);

			template<typename T>
			static std::vector<GameObject*> FindGameObjectsWithComponent();
			static std::vector<GameObject*> GetGameObjects();

			static bool Destroy(GameObject *object);
			template<typename T>
			static T* Instantiate(Scene* scene);
			template<typename T>
			static T* Instantiate(component::Transform* parent, Scene* scene);
			template<typename T>
			static T* Instantiate(math::Vector3 position, math::Quaternion rotation, Scene* scene);
			template<typename T>
			static T* Instantiate(math::Vector3 position, math::Quaternion rotation, component::Transform* parent, Scene* scene);

			virtual void Start() {}
			virtual void Update() {}
			virtual void FixedUpdate() {}
			virtual void LateUpdate() {}
			virtual void Render() {}
			virtual void OnCollision(component::RigidBodyComponent* other) {}
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
				T* component = Object::Instantiate<T>(this->GetScene());
				component->m_gameObject = this;
				m_components.push_back(component);
				component->Start();
				return component;
			}
			LOG("Invalid component");
			return NULL;
		}
		template<typename T>
		T* GameObject::GetComponent()
		{

			for (unsigned int i = 0; i < m_components.size(); i++)
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
			for (unsigned int i = 0; i < m_components.size(); i++)
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
			for (unsigned int i = 0; i < s_gameObjects.size(); i++)
			{
				T* component = s_gameObjects[i]->GetComponent<T>();
				if (component)
					gameObjectsWithComponent.push_back(s_gameObjects[i]);
			}
			return gameObjectsWithComponent;
		}

		template<typename T>
		inline T * GameObject::Instantiate(Scene * scene)
		{
			T* gameObject = Object::Instantiate<T>(scene);
			s_gameObjects.push_back(gameObject);
			gameObject->m_transform = gameObject->AddComponent<component::Transform>();
			gameObject->Start();
			return gameObject;
		}

		template<typename T>
		inline T * GameObject::Instantiate(component::Transform * parent, Scene * scene)
		{
			T* gameObject = Object::Instantiate<T>(scene);
			s_gameObjects.push_back(gameObject);
			gameObject->m_transform = gameObject->AddComponent<component::Transform>();
			gameObject->m_transform->SetParent(parent);
			gameObject->Start();
			return gameObject;
		}

		template<typename T>
		inline T * GameObject::Instantiate(math::Vector3 position, math::Quaternion rotation, Scene * scene)
		{
			T* gameObject = Object::Instantiate<T>(scene);
			s_gameObjects.push_back(gameObject);
			gameObject->m_transform = gameObject->AddComponent<component::Transform>();
			gameObject->m_transform->SetRotation(rotation);
			gameObject->m_transform->SetPosition(position);
			gameObject->Start();
			return gameObject;
		}

		template<typename T>
		inline T * GameObject::Instantiate(math::Vector3 position, math::Quaternion rotation, component::Transform * parent, Scene * scene)
		{
			T* gameObject = Object::Instantiate<T>(scene);
			s_gameObjects.push_back(gameObject);
			gameObject->m_transform = gameObject->AddComponent<component::Transform>();
			gameObject->m_transform->SetParent(parent);
			gameObject->m_transform->SetRotation(rotation);
			gameObject->m_transform->SetPosition(position);
			gameObject->Start();
			return gameObject;
		}


	}
}