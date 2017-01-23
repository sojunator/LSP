#pragma once
#include "../../Common.h"
#include <string>
#include "../../utils/d3d.h"
namespace thomas
{
	namespace graphics
	{
		namespace shader
		{
			class THOMAS_API Shader
			{
			private:
				struct Data
				{
					ID3D11VertexShader* vertexShader;
					ID3D11PixelShader* pixelShader;
					ID3DBlob* vs;
					ID3D10Blob* ps;
				};
			public:
				Shader(std::string name, std::string filePath);
				~Shader();
				bool Bind();
				bool Unbind();
				std::string GetName();
				std::string GetFilePath();

				ID3DBlob* Compile(std::string source, std::string profile, std::string main);

				ID3D11ShaderReflection* GetShaderReflection(ID3DBlob* shaderBlob);


				static Shader* GetCurrentBoundShader();

				
			private:
				Data m_data;
				std::string m_name;
				std::string m_filePath;

				std::vector<ID3D11Buffer*> m_constantBuffers;

				static Shader* s_currentBoundShader;
			};
		}
	}
}