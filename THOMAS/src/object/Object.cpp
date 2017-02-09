#include "Object.h"
#include "..\Scene.h"


namespace thomas
{
	namespace object
	{

		std::vector<Object*> Object::s_objects;
		Object::Object(std::string type, std::string name)
		{
			m_name = name;
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
		std::string Object::GetName()
		{
			return m_name;
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

		Object * Object::Instantiate(Object *object, Scene* scene)
		{
			s_objects.push_back(object);
			object->m_scene = scene;
			object->Start();
			return object;
		}

		std::vector<Object*> Object::GetObjects()
		{
			return s_objects;
		}
		Object * Object::GetObjectByName(std::string name)
		{
			for (int i = 0; i < s_objects.size(); i++)
			{
				if (s_objects[i]->m_name == name)
					return s_objects[i];
			}
			return NULL;
		}
	}
}

