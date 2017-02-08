#include "Object.h"


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
		bool Object::Destroy(Object *object)
		{
			delete object;
			return true;
		}

		Object * Object::Instantiate(Object *object, Scene* scene)
		{
			s_objects.push_back(object);
			object->Start();
			object->m_scene = scene;
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
		std::vector<Object*> Object::GetAllObjectsInScene(std::string sceneName)
		{
			std::vector<Object*> output;
			for (Object* object : s_objects)
				if (object->m_scene->GetName() == sceneName)
					output.push_back(object);
			return output;
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

