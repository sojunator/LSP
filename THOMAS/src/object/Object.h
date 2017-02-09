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
			Object(std::string type, std::string name);
			~Object();
			virtual bool Start() { return true; }
			virtual void Update() {}
			virtual void FixedUpdate() {}
			virtual void Render() {}

			std::string GetName();
			std::string GetType();
			Scene* GetScene();

			static bool Destroy(Object *object);
			//Clone object
			static Object* Instantiate(Object *object, Scene* scene);

			static std::vector<Object*> GetObjects();
			static Object* GetObjectByName(std::string name);

			static std::vector<Object*> GetAllObjectsInScene(Scene* scene);

		private:
			static std::vector<Object*> s_objects;
		protected:
			std::string m_name;
			std::string m_type;
			Scene* m_scene;
		};
	}
}