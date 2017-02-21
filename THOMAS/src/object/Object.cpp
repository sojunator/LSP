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
			m_alive = true;
		}
		Object::~Object()
		{
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
			object->m_alive = false;
			return true;
		}
		void Object::Destroy(Scene * scene)
		{
			for (int i = 0; i < s_objects.size(); ++i)
			{
				if (s_objects[i]->m_scene == scene)
					s_objects[i]->m_alive = false;
			}
				
		}

		

		void Object::Destroy()
		{
			s_objects.clear();
		}
		bool Object::IsAlive(const Object* object)
		{
			return object->m_alive;
		}
		std::vector<Object*> Object::GetObjects()
		{
			return s_objects;
		}
		Object * Object::GetObjectByType(std::string type)
		{
			for (unsigned int i = 0; i < s_objects.size(); i++)
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
				if (object->m_scene == scene && object->m_alive)
					output.push_back(object);
			return output;
		}
		void Object::Clean()
		{
			for (int i =0;i<s_objects.size();i++)
			{
				if (s_objects[i]->m_alive == false)
				{
					delete s_objects[i];
					s_objects.erase(s_objects.begin() + i);
					i -= 1;
				}
					
			}
		}
	}
}

