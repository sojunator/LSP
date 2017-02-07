#include "Scene.h"

namespace thomas
{
	std::vector<Scene*> Scene::s_scenes;
	Scene* Scene::s_currentScene;

	bool Scene::Init()
	{
		if (s_scenes[0])
		{
			s_currentScene = s_scenes[0];
			LOG("Scene set");
			return true;
		}
		LOG("No scenes");
			return false;
	}
	Scene* Scene::AddScene(Scene* scene)
	{
		s_scenes.push_back(scene);
		return scene;
	}
	bool Scene::DestroyScene(Scene* scene)
	{
		for (int i = 0; i < s_scenes.size(); ++i)
		{
			if (s_scenes[i] == scene)
			{
				s_scenes[i]->m_gameObjects.clear();
				s_scenes[i]->m_shaders.clear();
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
		for (int i = 0; i < s_currentScene->m_gameObjects.size(); ++i)
			s_currentScene->m_gameObjects[i]->Update();
	}
	std::vector<graphics::Shader*> Scene::GetShaders()
	{
		return m_shaders;
	}
	std::vector<graphics::Material*> Scene::GetMaterialsByShader(graphics::Shader * shader)
	{
		std::vector<graphics::Material*> output;
		for (graphics::Material* material : m_materials)
		{
			if (material->GetShader() == shader)
			{
				output.push_back(material);
			}
		}
		return output;
	}
	void Scene::Render()
	{
		if (s_currentScene == NULL)
		{
			LOG("No scene set")
			return;
		}
		for (object::component::Camera* camera : s_currentScene->m_cameras)
		{
			graphics::Renderer::Clear();
			graphics::Renderer::RenderSetup(camera);
			for (graphics::Shader* shader : s_currentScene->m_shaders)
			{
				shader->Bind();
				for (object::GameObject* lightGameObject : s_currentScene->GetObjectsByComponent<object::component::Light>())
				{
					graphics::LightManager::BindAllLights(); //lägga lights i scene också?
					for (graphics::Material* material : s_currentScene->GetMaterialsByShader(shader))
					{
						material->Bind();
						for (object::GameObject* gameObject : s_currentScene->GetObjectsByComponent<object::component::RenderComponent>())
						{
							object::component::RenderComponent* renderComponent = gameObject->GetComponent<object::component::RenderComponent>();
							graphics::Renderer::BindGameObjectBuffer(camera, gameObject);
							for (graphics::Mesh* mesh : renderComponent->GetModel()->GetMeshesByMaterial(material))
							{
								mesh->Bind();
								mesh->Draw();
							}
						}
						material->Unbind();
					}
					graphics::LightManager::Unbind();
				}
				shader->Unbind();
			}
			camera->BindSkybox();
			camera->UnbindSkybox();
			graphics::PostEffect::Render(graphics::Renderer::GetDepthBufferSRV(), graphics::Renderer::GetBackBuffer(), camera);
			//ThomasCore::GetSwapChain()->Present(0, 0);
		}
	}
	void Scene::RemoveObject(std::string name)
	{
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			if (m_gameObjects[i]->GetName() == name)
				m_gameObjects.erase(m_gameObjects.begin() + i);
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
