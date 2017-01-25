#pragma once
#include "../Common.h"
#include <string>
#include <vector>
namespace thomas
{
	namespace object
	{
		class THOMAS_API Object
		{
		private:
		public:
			Object(std::string type, std::string name);

			virtual bool Start() { return true; }
			virtual void Update() {}
			virtual void FixedUpdate() {}
			virtual void Render() {}

			std::string GetName();
			std::string GetType();

			static bool Destroy(Object *object);
			//Clone object
			static Object* Instantiate(Object *object);

			static std::vector<Object*> GetObjects();
			static Object* GetObjectByName(std::string name);

		private:
			static std::vector<Object*> s_objects;
		protected:
			std::string m_name;
			std::string m_type;
		};
	}
}