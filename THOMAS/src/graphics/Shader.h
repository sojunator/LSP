#pragma once
#include "../Common.h"
#include <string>
#include "../utils/d3d.h"
#include <vector>
namespace thomas
{
	class Scene;
	namespace graphics
	{

		class THOMAS_API Shader
		{
		public:
			enum class InputLayouts
			{
				STANDARD = 0,
				POST_EFFECT = 1
			};
			enum class ResourceType
			{
				GAME_OBJECT = 0,
				MATERIAL = 1,
				LIGHTS = 2
			};
		private:

			bool CreateInputLayout(InputLayouts layout);
			Shader(std::string name, InputLayouts inputLayout, std::string filePath);

			Shader(std::string name, InputLayouts inputLayout, std::string vertexShader, std::string geometryShader, std::string hullShader, std::string domainShader, std::string pixelShader);


		public:



			~Shader();
			bool Bind();
			bool Unbind();
			std::string GetName();
			std::string GetFilePath();

			bool BindBuffer(ID3D11Buffer* resource, ResourceType type);
			bool BindBuffer(ID3D11Buffer* resource, int slot);
			bool BindTextures(ID3D11ShaderResourceView* texture, int slot);
			bool BindTextureSampler(ID3D11SamplerState* sampler, int slot);
			bool BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY type);
			bool BindVertexBuffer(ID3D11Buffer* vertexBuffer, UINT stride, UINT offset);
			bool BindIndexBuffer(ID3D11Buffer* indexBuffer);
			

			static ID3DBlob* Compile(std::string source, std::string profile, std::string main);
			static Shader* CreateShader(std::string name, InputLayouts inputLayout, std::string filePath);
			static Shader* CreateShader(std::string name, InputLayouts inputLayout, std::string vertexShader, 
				std::string geometryShader, std::string hullShader, std::string domainShader, 
				std::string pixelShader);
			static Shader* GetCurrentBoundShader();
			static Shader* GetShaderByName(std::string name);
			static std::vector<Shader*> GetShadersByScene(Scene* scene);
			static std::vector<Shader*> GetLoadedShaders();
			static bool Destroy();
			static void Destroy(Scene* scene);

		private:
			struct Data
			{
				ID3DBlob* vs;
				ID3D11VertexShader* vertexShader;

				ID3DBlob* ps;
				ID3D11PixelShader* pixelShader;
				
				ID3DBlob* gs;
				ID3D11GeometryShader* geometryShader;

				ID3DBlob* hs;
				ID3D11HullShader* hullShader;

				ID3DBlob* ds;
				ID3D11DomainShader* domainShader;
				
				ID3D11InputLayout* inputLayout;
			};

			Data m_data;
			std::string m_name;
			std::string m_filePath;
			Scene* m_scene;

			static Shader* s_currentBoundShader;

			static std::vector<Shader*> s_loadedShaders;
		};
	}
}