#pragma once
#include "../Common.h"
#include <string>
#include <vector>
namespace thomas
{
	class Scene;
	namespace object
	{
		class THOMAS_API Object
		{
		private:
		public:
			Object(std::string type);
			~Object();
			virtual void Start() {}
			virtual void Update() {}
			virtual void FixedUpdate() {}
			virtual void Render() {}

			std::string GetType();
			Scene* GetScene();

			static bool Destroy(Object *object);
			static void Destroy(Scene* scene);
			static void Destroy();
			//Clone object
			template<typename T>
			static T* Instantiate(Scene* scene);

			static std::vector<Object*> GetObjects();
			static Object* GetObjectByType(std::string type);

			static std::vector<Object*> GetAllObjectsInScene(Scene* scene);

			static void Clean();

		private:
			bool m_alive;
			static std::vector<Object*> s_objects;
		protected:
			std::string m_type;
			Scene* m_scene;
		};
		template<typename T>
		inline T * Object::Instantiate(Scene * scene)
		{
			T* object = new T();
			s_objects.push_back(object);
			object->m_scene = scene;
			return object;
		}
	}
}