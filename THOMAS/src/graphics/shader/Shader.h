#pragma once
#include "../../Common.h"
#include <string>
#include "../../utils/d3d.h"
#include <vector>
namespace thomas
{
	namespace graphics
	{
		namespace shader
		{
			class THOMAS_API Shader
			{
			private:
				
				ID3DBlob* Compile(std::string source, std::string profile, std::string main);
				ID3D11ShaderReflection* GetShaderReflection(ID3DBlob* shaderBlob);
				void CreateBuffers(ID3DBlob* shaderBlob);
			public:

				enum class ResourceType
				{
					MVP_MATRIX = 0,
					MATERIAL = 1
				};

				Shader(std::string name, std::string filePath);
				~Shader();
				bool Bind();
				bool Unbind();
				std::string GetName();
				std::string GetFilePath();

				bool BindBuffer(ID3D11Buffer* resource, ResourceType type);
				bool BindBuffer(ID3D11Buffer* resource, int slot);
				bool BindTextures(ID3D11ShaderResourceView* texture, int slot);
				bool BindTextureSampler(ID3D11SamplerState* sampler, int slot);


				static Shader* GetCurrentBoundShader();

				
			private:
				struct Data
				{
					ID3D11VertexShader* vertexShader;
					ID3D11PixelShader* pixelShader;
					ID3DBlob* vs;
					ID3D10Blob* ps;
				};

				Data m_data;
				std::string m_name;
				std::string m_filePath;

				std::vector<ID3D11Buffer*> m_constantBuffers;

				static Shader* s_currentBoundShader;

				
			};
		}
	}
}