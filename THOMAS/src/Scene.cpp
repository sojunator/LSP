#include "Scene.h"
#include "graphics\PostEffect.h"
#include "graphics\Model.h"
#include "graphics\Sprite.h"

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
	void Scene::Destroy(Scene* scene)
	{
	}
	void Scene::LoadScene(Scene* scene)
	{
		s_currentScene = scene;
	}
	void Scene::UpdateCurrentScene()
	{

	}
	std::vector<graphics::Shader*> Scene::GetShaders()
	{
		return m_shaders;
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
			s_currentScene->Render(camera);
		}
	}
	void Scene::Render(object::component::Camera * camera)
	{
		graphics::Renderer::Clear();
		graphics::Renderer::RenderSetup(camera);
		if (s_currentScene)
			for (object::Object* object : object::Object::GetAllObjectsInScene(s_currentScene))
				object->Update();
		else
			LOG("No scene set");

		object::Object::Clean();

		for (graphics::Shader* shader : m_shaders)
		{
			shader->Bind();
			camera->BindReflection();
			for (object::GameObject* lightGameObject : object::GameObject::FindGameObjectsWithComponent<object::component::Light>())
			{
				graphics::LightManager::BindAllLights();
				for (graphics::Material* material : graphics::Material::GetMaterialsByShader(shader))
				{
					material->Bind();
					for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::RenderComponent>())
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
		graphics::PostEffect::Render(graphics::Renderer::GetDepthBufferSRV(), graphics::Renderer::GetBackBuffer(), camera);

		for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::SpriteComponent>())
		{

			for (object::component::SpriteComponent* sprite : gameObject->GetComponents<object::component::SpriteComponent>())
			{
				graphics::Sprite::RenderImage(sprite);
			}
		}

		for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::TextComponent>())
		{
			std::vector <object::component::TextComponent*> textComponent = gameObject->GetComponents<object::component::TextComponent>();

			for (object::component::TextComponent* text : gameObject->GetComponents<object::component::TextComponent>())
			{
				graphics::TextRender::RenderText(text);
			}
		}
		ThomasCore::GetSwapChain()->Present(0, 0);
	}
	graphics::Material * Scene::LoadMaterial(std::string type, graphics::Material* material)
	{
		return graphics::Material::RegisterNewMaterialType(type, material);
	}
	graphics::Shader * Scene::LoadShader(std::string name, thomas::graphics::Shader::InputLayouts inputLayout, std::string path)
	{
		graphics::Shader* shader = thomas::graphics::Shader::CreateShader(name, inputLayout, path);
		m_shaders.push_back(shader);
		return shader;
	}
	graphics::Model * Scene::LoadModel(std::string name, std::string path, std::string type)
	{
		return utils::AssimpLoader::LoadModel(name, path, type);
	}
	Scene * Scene::GetCurrentScene()
	{
		if (s_currentScene)
			return s_currentScene;
		LOG("No scene set")
			return NULL;
	}
}
