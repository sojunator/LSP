#include "Scene.h"
#include "graphics\PostEffect.h"
#include "graphics\Model.h"
#include "graphics\Sprite.h"
#include "graphics\Shader.h"

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
		graphics::Shader::Destroy(scene);
		object::Object::Destroy(scene);
		for (int i = 0; i < s_scenes.size(); ++i)
			if (s_scenes[i] == scene)
				s_scenes.erase(s_scenes.begin() + i);
	}
	void Scene::LoadScene(Scene* scene)
	{
		s_currentScene = scene;
	}
	void Scene::UpdateCurrentScene()
	{
		object::Object::Clean();
	}
	void Scene::Render()
	{
		if (s_currentScene == NULL)
		{
			LOG("No scene set")
				return;
		}
		std::vector<object::GameObject*> cameraObjects = object::GameObject::FindGameObjectsWithComponent<object::component::Camera>();
		std::vector<object::component::Camera*> cameras;
		for (object::GameObject* object : cameraObjects)
			cameras.push_back(object->GetComponent<object::component::Camera>());
		for (object::component::Camera* camera : cameras)
		{
			graphics::Renderer::Clear();
			graphics::Renderer::RenderSetup(camera);

			//Temp fix for ocean. Should be done in update
			if (s_currentScene)
				for (object::Object* object : object::Object::GetAllObjectsInScene(s_currentScene))
					object->Update();
			else
				LOG("No scene set");

			s_currentScene->Render3D(camera);
			s_currentScene->Render2D(camera);

			graphics::PostEffect::Render(graphics::Renderer::GetDepthBufferSRV(), graphics::Renderer::GetBackBuffer(), camera);

			ThomasCore::GetSwapChain()->Present(0, 0);
		}
	}
	void Scene::Render3D(object::component::Camera * camera)
	{

		//for (graphics::Shader* shader : graphics::Shader::GetShadersByScene(s_currentScene)) TODO: Set this up.
		for (graphics::Shader* shader : graphics::Shader::GetShadersByScene(s_currentScene))
		{
			shader->Bind();
			camera->BindReflection();
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

			shader->Unbind();
		}
		camera->BindSkybox();
		camera->UnbindSkybox();
	}



	void Scene::Render2D(object::component::Camera * camera)
	{


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
	}


	graphics::Material * Scene::LoadMaterial(std::string type, graphics::Material* material)
	{
		return graphics::Material::RegisterNewMaterialType(type, material);
	}
	graphics::Shader * Scene::LoadShader(std::string name, thomas::graphics::Shader::InputLayouts inputLayout, std::string path)
	{
		return thomas::graphics::Shader::CreateShader(name, inputLayout, path, this);
	}
	graphics::Shader * Scene::LoadShader(std::string name, thomas::graphics::Shader::InputLayouts inputLayout, std::string vertexShader, std::string geometryShader, std::string hullShader, std::string domainShader, std::string pixelShader)
	{
		return thomas::graphics::Shader::CreateShader(name, inputLayout, vertexShader,geometryShader, hullShader, domainShader, pixelShader, this);
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
