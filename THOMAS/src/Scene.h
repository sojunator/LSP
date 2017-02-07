#pragma once
#include "Common.h"
#include "object\GameObject.h"
#include "graphics\Material.h"
#include "graphics\Renderer.h"
#include <vector>

namespace thomas
{
	class THOMAS_API Scene
	{
	private:
	public:
		static bool Init();
		static void AddScene(Scene* scene);
		static bool DestroyScene(Scene* scene);
		static void LoadScene(Scene* scene); //Set s_currentScene
		void static Update();
		std::vector<graphics::Shader*> GetShaders();
		std::vector<graphics::Material*> GetMaterialsByShader(graphics::Shader* shader);
		template<typename T>
		std::vector<object::GameObject*> GetObjectsByComponent();
		static void Render();
		void RemoveObject(std::string name);
		void RemoveMaterial(std::string name);
		void RemoveShader(std::string name);
		void RemoveModel(std::string name);
		static Scene* GetCurrentScene();
	private:
		static std::vector<Scene*> s_scenes;
		static Scene* s_currentScene;
	protected:
		std::vector<object::GameObject*> m_gameObjects;
		std::vector<graphics::Material*> m_materials;
		std::vector<graphics::Shader*> m_shaders;
		std::vector<graphics::Model*> m_models;
		std::vector<object::component::Camera*> m_cameras;
	};
}