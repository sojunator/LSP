#pragma once
#include "graphics\Renderer.h"
#include "graphics\ParticleSystem.h"
#include "PlayerStats.h"
namespace thomas
{
	class THOMAS_API Scene
	{
	private:
		std::vector<object::component::RenderComponent*> GetAllRenderComponents();
	public:
		
		static void UnloadScene();
		void static UpdateCurrentScene();
		static void Render();
		void Render3D(object::component::Camera* camera);
		void Render2D(object::component::Camera* camera);
		graphics::Material* LoadMaterial(std::string type, graphics::Material* material);
		//void RemoveMaterial(std::string name);
		graphics::Shader* LoadShader(std::string name, graphics::Shader::InputLayouts inputLayout, std::string path);
		graphics::Shader* LoadShader(std::string name, thomas::graphics::Shader::InputLayouts inputLayout, std::string vertexShader, std::string geometryShader, std::string hullShader, std::string domainShader, std::string pixelShader);
		//void RemoveShader(std::string name);
		graphics::Model* LoadModel(std::string name, std::string path, std::string type);
		//void RemoveModel(std::string name);
		template<typename T>
		static Scene* LoadScene(); //Set s_currentScene
		template<typename T>
		T * LoadObject();
		template<typename T>
		T * LoadObject(object::component::Transform* parent);
		template<typename T>
		T * LoadObject(thomas::math::Vector3 position, thomas::math::Quaternion rotation);
		template<typename T>
		T * LoadObject(thomas::math::Vector3 position, thomas::math::Quaternion rotation, object::component::Transform* parent);
		//void UnloadObject(std::string name);
		static Scene* GetCurrentScene();
		std::string GetName() { return m_name; }
		static void SetStatPointer(PlayerStats* stats);
	private:
		static Scene* s_currentScene;
		static bool s_drawDebugPhysics;
		static PlayerStats* s_stats;
	protected:
		std::string m_name;
		Scene(std::string name);
	};
	template<typename T>
	inline Scene * Scene::LoadScene()
	{
		if (s_currentScene)
			UnloadScene();
		Scene* scene = new T();
		s_currentScene = scene;
		LOG("Scene " + scene->GetName() + " set");
		//Flush inputs
		Input::Update();
		return scene;
	}
	template<typename T>
	T* Scene::LoadObject()
	{
		return object::GameObject::Instantiate<T>(this);
	}
	template<typename T>
	T* Scene::LoadObject(object::component::Transform* parent)
	{
		return object::GameObject::Instantiate<T>(parent, this);
	}
	template<typename T>
	T* Scene::LoadObject(thomas::math::Vector3 position, thomas::math::Quaternion rotation)
	{
		return object::GameObject::Instantiate<T>(position, rotation, this);
	}
	template<typename T>
	T* Scene::LoadObject(thomas::math::Vector3 position, thomas::math::Quaternion rotation, object::component::Transform* parent)
	{
		return object::GameObject::Instantiate<T>(position, rotation, parent, this);
	}
}