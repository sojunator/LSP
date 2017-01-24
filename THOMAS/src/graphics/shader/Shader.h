#pragma once
#include "../../Common.h"
#include <string>
#include "../../utils/d3d.h"
#include <vector>
#include "../Mesh.h"
namespace thomas
{
	namespace graphics
	{
		namespace shader
		{
			enum class InputLayouts
			{
				STANDARD = 0
			};
			enum class ResourceType
			{
				MVP_MATRIX = 0,
				MATERIAL = 1
			};

			class THOMAS_API Shader
			{
			private:
				
				ID3DBlob* Compile(std::string source, std::string profile, std::string main);
				bool CreateInputLayout(InputLayouts layout);
			public:

				Shader(std::string name, std::string filePath, InputLayouts inputLayout);
				~Shader();
				bool Bind();
				bool Unbind();
				std::string GetName();
				std::string GetFilePath();

				bool BindBuffer(ID3D11Buffer* resource, ResourceType type);
				bool BindBuffer(ID3D11Buffer* resource, int slot);
				bool BindTextures(ID3D11ShaderResourceView* texture, int slot);
				bool BindTextureSampler(ID3D11SamplerState* sampler, int slot);
				bool SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY type);
				bool SetVertexBuffer(ID3D11Buffer* vertexBuffer, UINT stride, UINT offset);
				bool SetIndexBuffer(ID3D11Buffer* indexBuffer);
				bool SetMeshData(MeshData* meshData);

				static Shader* GetCurrentBoundShader();
				static Shader* GetShader(std::string name);

				
				
			private:
				struct Data
				{
					ID3D11VertexShader* vertexShader;
					ID3D11PixelShader* pixelShader;
					ID3DBlob* vs;
					ID3D10Blob* ps;
					ID3D11InputLayout* inputLayout;
				};

				Data m_data;
				std::string m_name;
				std::string m_filePath;

				std::vector<ID3D11Buffer*> m_constantBuffers;

				static Shader* s_currentBoundShader;

				static std::vector<Shader*> s_loadedShaders;


				
			};
		}
	}
}