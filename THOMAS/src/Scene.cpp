#include "Scene.h"

namespace thomas
{
	std::vector<Scene*> Scene::s_scenes;
	Scene* Scene::s_currentScene;

	bool Scene::Init()
	{
		s_currentScene = s_scenes[0];
		return true;
	}
	void Scene::AddScene(Scene* scene)
	{
		s_scenes.push_back(scene);
	}
	bool Scene::DestroyScene(Scene* scene)
	{
		for (int i = 0; i < s_scenes.size(); ++i)
		{
			if (s_scenes[i] == scene)
			{
				s_scenes[i]->m_objects.clear();
				s_scenes[i]->m_materials.clear();
				s_scenes[i]->m_shaders.clear();
				s_scenes[i]->m_models.clear();
				s_scenes.erase(s_scenes.begin() + i);
			}
		}
		return true;
	}
	void Scene::LoadScene(Scene* scene)
	{
		s_currentScene = scene;
	}
	void Scene::Update()
	{
		for (int i = 0; i < s_currentScene->m_objects.size(); ++i)
			s_currentScene->m_objects[i]->Update();
	}
	std::vector<graphics::Shader*> Scene::GetShaders()
	{
		return m_shaders;
	}
	void Scene::RemoveObject(std::string name)
	{
		for (int i = 0; i < m_objects.size(); ++i)
		{
			if (m_objects[i]->GetName() == name)
				m_objects.erase(m_objects.begin() + i);
		}
	}
	Scene * Scene::GetCurrentScene()
	{
		if (s_currentScene)
			return s_currentScene;
		LOG("No scene set")
		return NULL;
	}
}
