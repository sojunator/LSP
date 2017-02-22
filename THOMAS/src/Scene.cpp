#include "Scene.h"
#include "graphics\PostEffect.h"
#include "graphics\Model.h"
#include "graphics\Sprite.h"
#include "graphics\Shader.h"
#include "utils\DebugTools.h"


namespace thomas
{
	Scene* Scene::s_currentScene;
	bool Scene::s_drawDebugPhysics;
	void Scene::UnloadScene()
	{
		utils::DebugTools::RemoveAllVariables();
		graphics::LightManager::Destroy();
		graphics::Material::Destroy();
		graphics::Shader::Destroy();
		graphics::Texture::Destroy();
		graphics::Model::Destroy();	
		object::Object::Destroy(s_currentScene);
		delete s_currentScene;
		s_currentScene = nullptr;
	}
	void Scene::UpdateCurrentScene()
	{
		//Temp fix for ocean.
		graphics::Renderer::RenderSetup(NULL);
		if (s_currentScene)
			for (object::Object* object : object::Object::GetAllObjectsInScene(s_currentScene))
				object->Update();
		else
			LOG("No scene set");
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
			if(s_drawDebugPhysics)
				Physics::DrawDebug(camera);
			s_currentScene->Render2D(camera);

			graphics::PostEffect::Render(graphics::Renderer::GetDepthBufferSRV(), graphics::Renderer::GetBackBuffer(), camera);
			
			utils::DebugTools::Draw();
			ThomasCore::GetSwapChain()->Present(0, 0);
		}
	}
	void Scene::Render3D(object::component::Camera * camera)
	{

		graphics::ParticleSystem::DrawParticles(camera);
		for (graphics::Shader* shader : graphics::Shader::GetShadersByScene(s_currentScene))
		{
			if (shader->GetName() == "oceanShader")
				continue;
			shader->Bind();
			camera->BindReflection();
			graphics::LightManager::BindAllLights();
			for (graphics::Material* material : graphics::Material::GetMaterialsByShader(shader))
			{
				material->Bind();
				for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::RenderComponent>())
				{
					
					for (object::component::RenderComponent* renderComponent : gameObject->GetComponents<object::component::RenderComponent>())
					{
						if(renderComponent->GetModel())
							for (graphics::Mesh* mesh : renderComponent->GetModel()->GetMeshesByMaterial(material))
							{
								graphics::Renderer::BindGameObjectBuffer(camera, gameObject);
								mesh->Bind();
								mesh->Draw();
							}
					}
				}
				material->Unbind();
			}

			shader->Unbind();
		}


		graphics::Shader* oceanShader = graphics::Shader::GetShaderByName("oceanShader");
		if (oceanShader)
		{
			DirectX::CommonStates state(ThomasCore::GetDevice());
			graphics::Renderer::BindDepthBufferTexture();
			ThomasCore::GetDeviceContext()->OMSetBlendState(state.NonPremultiplied(), NULL, 0xFFFFFFFF);
			oceanShader->Bind();
			camera->BindReflection();
		graphics::LightManager::BindAllLights();
			for (graphics::Material* material : graphics::Material::GetMaterialsByShader(oceanShader))
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
				
			oceanShader->Unbind();
			graphics::Renderer::UnbindDepthBufferTexture();
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
	Scene::Scene(std::string name)
	{
		m_name = name;
		s_drawDebugPhysics = false;
		utils::DebugTools::AddBool(s_drawDebugPhysics, "Draw Debug Physics");
	}
}
