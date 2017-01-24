#include "Object.h"


namespace thomas
{
	namespace object
	{

		std::vector<Object*> Object::s_objects;
		std::string Object::GetName()
		{
			return m_name;
		}
		bool Object::Destroy(Object  *object)
		{
			for (int i = 0; i < s_objects.size(); i++)
			{
				if (s_objects[i] == object)
				{
					s_objects.erase(s_objects.begin() + i);
					delete object;
					return true;
				}
			}
			return false;
		}

		Object * Object::Instantiate(Object *object)
		{
			s_objects.push_back(object);
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

