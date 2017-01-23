#include "Shader.h"
#include "../../ThomasCore.h"
#include "ShaderManager.h"
namespace thomas
{
	namespace graphics
	{
		namespace shader
		{

			Shader* Shader::s_currentBoundShader;


			ID3DBlob* Shader::Compile(std::string source, std::string profile, std::string main)
			{
				ID3DBlob* shaderBlob;
				ID3DBlob* errorBlob;
				HRESULT status = D3DCompile(source.c_str(), source.size(), NULL, NULL, NULL, main.c_str(), profile.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
				if (errorBlob)
				{
					if (errorBlob->GetBufferSize())
					{
						LOG("Shader Compiler errors:  " + errorBlob->GetBufferPointer());
					}
					errorBlob->Release();
				}
				if (status == S_OK)
					return shaderBlob;
				return NULL;
			}

			ID3D11ShaderReflection * Shader::GetShaderReflection(ID3DBlob * shaderBlob)
			{
				ID3D11ShaderReflection* shaderReflection;
				HRESULT result = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection);
				if (result == S_OK)
				{
					return shaderReflection;
				}
				else
				{
					LOG("Shader reflection error");
				}
				return NULL;
			}


			Shader::Shader(std::string name, std::string filePath)
			{
				m_name = name;
				m_filePath = filePath;

				m_data.vs = Compile(filePath, "vs_5_0", "VSMain");
				m_data.ps = Compile(filePath, "ps_5_0", "PSMain");

				ThomasCore::GetDevice()->CreateVertexShader(m_data.vs->GetBufferPointer(), m_data.vs->GetBufferSize(), NULL, &m_data.vertexShader);
				ThomasCore::GetDevice()->CreatePixelShader(m_data.ps->GetBufferPointer(), m_data.ps->GetBufferSize(), NULL, &m_data.pixelShader);
				//ThomasCore::GetDevice()->CreateVertexShader(m_data.vs->GetBufferPointer(), m_data.vs->GetBufferSize(), NULL, &m_data.vertexShader);
				

				ShaderManager::AddShader(this);

			}

			Shader::~Shader()
			{
				m_data.vertexShader->Release();
				m_data.pixelShader->Release();
			}

			bool Shader::Bind()
			{
				s_currentBoundShader = this;
				ThomasCore::GetDeviceContext()->VSSetShader(m_data.vertexShader, NULL, 0);
				ThomasCore::GetDeviceContext()->PSSetShader(m_data.pixelShader, NULL, 0);
				return true;
			}
			bool Shader::Unbind()
			{
				if (s_currentBoundShader == this)
				{
					ThomasCore::GetDeviceContext()->VSSetShader(NULL, NULL, 0);
					ThomasCore::GetDeviceContext()->PSSetShader(NULL, NULL, 0);
					s_currentBoundShader = nullptr;
					return true;
				}
				return false;
			}
			std::string Shader::GetName()
			{
				return std::string();
			}
			std::string Shader::GetFilePath()
			{
				return std::string();
			}
			Shader * Shader::GetCurrentBoundShader()
			{
				return nullptr;
			}
		}
	}
}