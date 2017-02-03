#include "Scene.h"

namespace thomas
{
	std::vector<Scene> Scene::s_scenes;
	Scene* Scene::s_currentScene;

	bool Scene::Init()
	{
		return true;
	}

	Scene* Scene::LoadScene(std::string name)
	{
		for (int i = 0; i < s_scenes.size(); ++i)
		{
			if (s_scenes[i].m_name == name)	
				return s_currentScene = &s_scenes[i];
		}
		return NULL;
	}

	bool Scene::UnLoadScene()
	{
		m_objects.clear();
		return true;
	}
	void Scene::Update()
	{
		for (int i = 0; i < s_currentScene->m_objects.size(); ++i)
			s_currentScene->m_objects[i]->Update();
	}
	void Scene::LoadObject(object::Object* object)
	{
		m_objects.push_back(object);
	}
	void Scene::UnLoadObject(std::string name)
	{
		for (int i = 0; i < m_objects.size(); ++i)
		{
			if (m_objects[i]->GetName() == name)
				m_objects.erase(m_objects.begin() + i);
		}
	}
}
