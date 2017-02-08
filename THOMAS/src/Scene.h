#pragma once
#include "graphics\Renderer.h"

namespace thomas
{
	class THOMAS_API Scene
	{
	public:
		static bool Init();
		static Scene* AddScene(Scene* scene);
		static bool DestroyScene(Scene* scene);
		static void LoadScene(Scene* scene); //Set s_currentScene
		void static Update();
		std::vector<graphics::Shader*> GetShaders();
		std::vector<graphics::Material*> GetMaterialsByShader(graphics::Shader* shader);
		template<typename T>
		std::vector<object::GameObject*> GetObjectsByComponent();
		static void Render();
		void Render(object::component::Camera* camera);
		void CreateMaterial();
		void RemoveMaterial(std::string name);
		void CreateShader();
		void RemoveShader(std::string name);
		void CreateModel();
		void RemoveModel(std::string name);
		static Scene* GetCurrentScene();
	private:
		static std::vector<Scene*> s_scenes;
		static Scene* s_currentScene;
	protected:
		std::vector<object::GameObject*> m_gameObjects;
		std::vector<object::Object*> m_objects;
		std::vector<graphics::Shader*> m_shaders;
		std::vector<graphics::Model*> m_models;
		std::vector<object::component::Camera*> m_cameras;
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