#pragma once
#include "component\Components.h"
#include "Object.h"
#include <vector>
namespace thomas
{
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

			static GameObject* Find(std::string name);

			virtual bool Start() { return true; }
			virtual void Update() {}
			virtual void FixedUpdate() {}
			virtual void Render() {}

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


	}
}