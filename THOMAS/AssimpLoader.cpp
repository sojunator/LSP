#include "AssimpLoader.h"

namespace thomas
{
	namespace graphics
	{

		AssimpLoader::AssimpLoader()
		{
		}


		AssimpLoader::~AssimpLoader()
		{
		}

		void AssimpLoader::LoadModel(std::string path)
		{
			// Read file via ASSIMP
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
			// Check for errors
			if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
				return;
			}
		}

		Mesh* AssimpLoader::ProcessMesh(aiMesh * mesh, const aiScene * scene)
		{
			// Data to fill
			std::vector <Vertex> vertices;
			std::vector <int> indices;
			std::string name = mesh->mName.C_Str();
			
			//vector<Texture> textures;

			// Walk through each of the mesh's vertices
			for (int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				math::Vector3 vector;

				// Positions
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.position = vector;

				// Normals
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;

				// Texture Coordinates
				if (mesh->mTextureCoords[0])
				{
					math::Vector2 vec;

					// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.uv = vec;
				}
				else
					vertex.uv = math::Vector2(0.0f, 0.0f);
				vertices.push_back(vertex);
			}

			// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
			for (int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// Retrieve all indices of the face and store them in the indices vector
				for (int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			// Process materials
			//if (mesh->mMaterialIndex >= 0)
			//{
			//	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			//	// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
			//	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			//	// Same applies to other texture as the following list summarizes:
			//	// Diffuse: texture_diffuseN
			//	// Specular: texture_specularN
			//	// Normal: texture_normalN

			//	// 1. Diffuse maps
			//	vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			//	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			//	// 2. Specular maps
			//	vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			//	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			//}

			// Return a mesh object created from the extracted mesh data
			return &Mesh(vertices, indices, name);
		}

		void AssimpLoader::ProcessNode(aiNode * node, const aiScene * scene)
		{
			Model model;
			// Process each mesh located at the current node
			for (int i = 0; i < node->mNumMeshes; i++)
			{
				// The node object only contains indices to index the actual objects in the scene. 
				// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				model.meshes.push_back(ProcessMesh(mesh, scene));
			}
			// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
			for (int i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene);
			}
		}
	}
}
