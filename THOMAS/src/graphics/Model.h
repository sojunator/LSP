#pragma once
#include "../Common.h"
#include "Mesh.h"
#include "Material.h"
namespace thomas {
	namespace graphics {
		class THOMAS_API Model {
		private:
			Model(std::string name, std::vector<Mesh>& meshes);
		public:
			static Model* CreateModel(std::string name, std::vector<Mesh>& meshes);
			static Model* GetModelByName(std::string name);
			static std::vector<Model*> GetLoadedModels();
			std::string GetName();
			std::vector<Mesh*> GetMeshesByMaterial(material::Material* material);
			std::vector<Mesh*> GetMeshesByMaterial(std::string name);
			std::vector<Mesh>* GetMeshes();
		private:
			static std::vector<Model*> s_loadedModels;
			std::vector<Mesh> m_meshes;
			std::string m_name;
		};
	}
}