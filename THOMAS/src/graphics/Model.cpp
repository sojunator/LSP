#include "Model.h"

namespace thomas {
	namespace graphics {

		std::vector<Model*> Model::s_loadedModels;
		Model::Model(std::string name, std::vector<Mesh*> meshes)
		{
			m_name = name;
			m_meshes = meshes;
		}

		Model * Model::CreateModel(std::string name, std::vector<Mesh*> meshes)
		{
			Model* existingModel = GetModelByName(name);
			if (existingModel)
				return existingModel;
			else
			{
				Model* newModel = new Model(name, meshes);
				s_loadedModels.push_back(newModel);
				return newModel;
			}
		}

		Model * Model::GetModelByName(std::string name)
		{
			for (unsigned int i = 0; i < s_loadedModels.size(); i++)
			{
				if (s_loadedModels[i]->GetName() == name)
					return s_loadedModels[i];
			}
			return NULL;
		}

		std::vector<Model*> Model::GetLoadedModels()
		{
			return s_loadedModels;
		}


		std::string Model::GetName()
		{
			return m_name;
		}

		std::vector<Mesh*> Model::GetMeshesByMaterial(Material* material)
		{
			std::vector<Mesh*> meshes;
			for (unsigned int i = 0; i < m_meshes.size(); i++)
			{
				if (m_meshes[i]->GetMaterial() == material)
					meshes.push_back(m_meshes[i]);
			}
			return meshes;
		}

		std::vector<Mesh*> Model::GetMeshesByMaterial(std::string name)
		{
			std::vector<Mesh*> meshes;
			for (unsigned int i = 0; i < m_meshes.size(); i++)
			{
				if (m_meshes[i]->GetMaterial()->GetName() == name)
					meshes.push_back(m_meshes[i]);
			}
			return meshes;
		}

		std::vector<Mesh*> Model::GetMeshes()
		{
			return m_meshes;
		}

		void Model::Destroy()
		{
			for (unsigned int i = 0; i < s_loadedModels.size(); i++)
			{
				delete s_loadedModels[i];
			}
		}

		Model::~Model()
		{
			for (unsigned int i = 0; i < m_meshes.size(); i++)
			{
				delete m_meshes[i];
			}
		}

	}
}