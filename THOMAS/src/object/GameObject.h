#pragma once
#include "Object.h"
#include "component\Components.h"
#include <vector>
namespace thomas
{
	namespace object
	{
		class THOMAS_API GameObject : public Object
		{
		private:
		public:
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
			bool m_active;
			component::Transform* m_transform;
			std::vector<component::Component*> m_components;
			static std::vector<GameObject*> s_gameObjects;
		protected:
		};
	}
}