#pragma once
#include "graphics\Renderer.h"
#include "graphics\Model.h"
#include "object\Object.h"

namespace thomas
{
	class THOMAS_API Scene
	{
	public:
		static bool Init();
		static Scene* AddScene(Scene* scene);
		static bool DestroyScene(Scene* scene);
		static void LoadScene(std::string name); //Set s_currentScene
		virtual void LoadScene() = 0;
		void static UpdateCurrentScene();
		std::vector<graphics::Shader*> GetShaders();
		//std::vector<graphics::Material*> GetMaterialsByShader(graphics::Shader* shader);
		template<typename T>
		std::vector<object::GameObject*> GetObjectsByComponent();
		static void Render();
		void Render(object::component::Camera* camera);
		graphics::Material * LoadMaterialType(std::string name, graphics::Material * material);
		graphics::Shader * LoadShader(std::string name, graphics::Shader::InputLayouts inputLayout, std::string path);
		graphics::Model * LoadModel(std::string name, std::string path, std::string materialName);
		//void RemoveMaterial(std::string name);
		//void RemoveShader(std::string name);
		//void RemoveModel(std::string name);
		static Scene* GetCurrentScene();
		std::string GetName();
	private:
		static std::vector<Scene*> s_scenes;
		static Scene* s_currentScene;
	protected:
		std::vector<object::GameObject*> m_gameObjects;
		std::vector<object::Object*> m_objects;
		std::vector<graphics::Shader*> m_shaders;
		std::vector<graphics::Model*> m_models;
		std::vector<object::component::Camera*> m_cameras;
		std::string m_name;
		Scene(std::string name);
	};
	template<typename T>
	inline std::vector<object::GameObject*> Scene::GetObjectsByComponent()
	{
		std::vector<object::GameObject*> output;
		for (int i = 0; i < m_gameObjects.size(); ++i)
		{
			T* component = m_gameObjects[i]->GetComponent<T>();
			if (component)
				output.push_back(m_gameObjects[i]);
		}
		return output;
	}
}