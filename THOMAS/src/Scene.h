#pragma once
#include "graphics\Renderer.h"

namespace thomas
{
	class THOMAS_API Scene
	{
	public:
		static bool Init();
		static Scene* AddScene(Scene* scene);
		static void Destroy(Scene* scene);
		static void LoadScene(Scene* scene); //Set s_currentScene
		static void LoadScene(int sceneIndex);
		void static UpdateCurrentScene();
		std::vector<graphics::Shader*> GetShaders();
		static void Render();
		void Render3D(object::component::Camera* camera);
		void Render2D(object::component::Camera* camera);
		graphics::Material* LoadMaterial(std::string type, graphics::Material* material);
		//void RemoveMaterial(std::string name);
		graphics::Shader* LoadShader(std::string name, graphics::Shader::InputLayouts inputLayout, std::string path);
		//void RemoveShader(std::string name);
		graphics::Model* LoadModel(std::string name, std::string path, std::string type);
		//void RemoveModel(std::string name);
		static Scene* GetCurrentScene();
	private:
		static std::vector<Scene*> s_scenes;
		static Scene* s_currentScene;
	protected:
		std::vector<graphics::Shader*> m_shaders;
		std::vector<object::component::Camera*> m_cameras;
		std::string m_name;
		Scene(std::string name) { m_name = name; }
		Scene() { m_name = "You forgot to name your scene, loser-Preben"; }
	};
}