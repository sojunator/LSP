#include "Object.h"
#include "..\Scene.h"


namespace thomas
{
	namespace object
	{

		std::vector<Object*> Object::s_objects;
		Object::Object(std::string type)
		{
			m_type = type;
		}
		Object::~Object()
		{
			for (int i = 0; i < s_objects.size(); i++)
			{
				if (s_objects[i] == this)
				{
					s_objects.erase(s_objects.begin() + i);
				}
			}
		}
		std::string Object::GetType()
		{
			return m_type;
		}
		Scene* Object::GetScene()
		{
			return m_scene;
		}
		bool Object::Destroy(Object *object)
		{
			delete object;
			return true;
		}

		std::vector<Object*> Object::GetObjects()
		{
			return s_objects;
		}
		Object * Object::GetObjectByType(std::string type)
		{
			for (int i = 0; i < s_objects.size(); i++)
			{
				if (s_objects[i]->m_type == type)
					return s_objects[i];
			}
			return NULL;
		}
		std::vector<Object*> Object::GetAllObjectsInScene(Scene * scene)
		{
			std::vector<Object*> output;
			for (Object* object : s_objects)
				if (object->m_scene == scene)
					output.push_back(object);
			return output;
		}
	}
}

