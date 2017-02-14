#pragma once
#include "graphics\Renderer.h"

namespace thomas
{
	class THOMAS_API Scene
	{
	public:
		static bool Init();
		static Scene* AddScene(Scene* scene);
		static void UnloadScene(Scene* scene);
		static void LoadScene(Scene* scene); //Set s_currentScene
		void static UpdateCurrentScene();
		static void Render();
		void Render3D(object::component::Camera* camera);
		void Render2D(object::component::Camera* camera);
		graphics::Material* LoadMaterial(std::string type, graphics::Material* material);
		//void RemoveMaterial(std::string name);
		graphics::Shader* LoadShader(std::string name, graphics::Shader::InputLayouts inputLayout, std::string path);
		graphics::Shader * LoadShader(std::string name, thomas::graphics::Shader::InputLayouts inputLayout, std::string vertexShader, std::string geometryShader, std::string hullShader, std::string domainShader, std::string pixelShader);
		//void RemoveShader(std::string name);
		graphics::Model* LoadModel(std::string name, std::string path, std::string type);
		//void RemoveModel(std::string name);
		template<typename T>
		T * LoadObject();
		template<typename T>
		T * LoadObject(object::component::Transform* parent);
		template<typename T>
		T * LoadObject(thomas::math::Vector3 position, thomas::math::Quaternion rotation);
		template<typename T>
		T * LoadObject(thomas::math::Vector3 position, thomas::math::Quaternion rotation, object::component::Transform* parent);
		static Scene* GetCurrentScene();
	private:
		static std::vector<Scene*> s_scenes;
		static Scene* s_currentScene;
	protected:
		std::string m_name;
		Scene(std::string name) { m_name = name; }
		Scene() { m_name = "You forgot to name your scene, loser-Preben"; }
	};
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
		return object::GameObject::Instantiate<T>(position, rotation, this)
	}
	template<typename T>
	T* Scene::LoadObject(thomas::math::Vector3 position, thomas::math::Quaternion rotation, object::component::Transform* parent)
	{
		return object::GameObject::Instantiate<T>(position, rotation, parent, this)
	}
}