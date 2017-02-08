#include "Scene.h"
#include "graphics\PostEffect.h"
#include "graphics\Model.h"

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
			s_currentScene->m_gameObjects[i]->SceneUpdate();
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
		for(object::component::Camera* camera : s_currentScene->m_cameras)
		{
			s_currentScene->Render(camera);
		}
	}
	void Scene::Render(object::component::Camera * camera)
	{
			graphics::Renderer::Clear();
			graphics::Renderer::RenderSetup(camera);
			for (graphics::Shader* shader : m_shaders)
			{
				shader->Bind();
				for (object::GameObject* lightGameObject : GetObjectsByComponent<object::component::Light>())
				{
					graphics::LightManager::BindAllLights();
					for (graphics::Material* material : graphics::Material::GetMaterialsByShader(shader))
					{
						material->Bind();
						for (object::GameObject* gameObject : GetObjectsByComponent<object::component::RenderComponent>())
						{
							graphics::Renderer::BindGameObjectBuffer(camera, gameObject);
							for (object::component::RenderComponent* renderComponent : gameObject->GetComponents<object::component::RenderComponent>())
							{
								for (graphics::Mesh* mesh : renderComponent->GetModel()->GetMeshesByMaterial(material))
								{
									mesh->Bind();
									mesh->Draw();
								}
							}
							graphics::Renderer::UnBindGameObjectBuffer();
						}
						material->Unbind();
					}
					graphics::LightManager::Unbind();
				}
				shader->Unbind();
			}
			camera->BindSkybox();
			camera->UnbindSkybox();
			//graphics::PostEffect::Render(graphics::Renderer::GetDepthBufferSRV(), graphics::Renderer::GetBackBuffer(), camera);
			ThomasCore::GetSwapChain()->Present(0, 0);
	}
	Scene * Scene::GetCurrentScene()
	{
		if (s_currentScene)
			return s_currentScene;
		LOG("No scene set")
		return NULL;
	}
}
