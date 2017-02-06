#pragma once
#include "Common.h"
#include "object\GameObject.h"
#include "graphics\Material.h"
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
		void RemoveObject(std::string name);
		void RemoveMaterial(std::string name);
		void RemoveShader(std::string name);
		void RemoveModel(std::string name);
		static Scene* GetCurrentScene();
	private:
		static std::vector<Scene*> s_scenes;
		static Scene* s_currentScene;
	protected:
		std::vector<object::Object*> m_objects;
		std::vector<graphics::Material*> m_materials;
		std::vector<graphics::Shader*> m_shaders;
		std::vector<graphics::Model*> m_models;
	};
}