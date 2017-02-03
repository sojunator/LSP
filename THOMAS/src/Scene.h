#pragma once
#include "Common.h"
#include "object\GameObject.h"
#include <vector>

namespace thomas
{
	class THOMAS_API Scene
	{
	public:
		static bool Init();
		static Scene* LoadScene(std::string name);
		bool UnLoadScene();
		void static Update();
		void LoadObject(object::Object* object);
		void UnLoadObject(std::string name);
		void LoadResource();
		void UnLoadResource();
	private:
		std::vector<object::Object*> m_objects;
		std::string m_name;
		static std::vector<Scene> s_scenes;
		static Scene* s_currentScene;
	};
}