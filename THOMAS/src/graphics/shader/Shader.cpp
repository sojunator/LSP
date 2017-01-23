#include "Shader.h"
#include "../../ThomasCore.h"
#include "ShaderManager.h"
#include <AtlBase.h>
#include <atlconv.h>
namespace thomas
{
	namespace graphics
	{
		namespace shader
		{

			Shader* Shader::s_currentBoundShader;
			static Shader* s_currentBoundShader;

			ID3DBlob* Shader::Compile(std::string source, std::string profile, std::string main)
			{
				ID3DBlob* shaderBlob;
				ID3DBlob* errorBlob;
				
			
				HRESULT status = D3DCompileFromFile(CA2W(source.c_str()), nullptr, nullptr, main.c_str(), profile.c_str(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);
		

				
				if (status != S_OK)
				{
					LOG(status);
				}
				if (errorBlob)
				{
					if (errorBlob->GetBufferSize())
					{
						LOG("Shader Compiler errors: " << (char*)errorBlob->GetBufferPointer());
					}
					errorBlob->Release();
				}
				else if (status == S_OK)
				{
					LOG("Shader " << m_name << " " << main << " Sucessfully loaded");
					return shaderBlob;
				}
					
				return NULL;
			}

			ID3D11ShaderReflection * Shader::GetShaderReflection(ID3DBlob* shaderBlob)
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

			void Shader::CreateBuffers(ID3DBlob* shaderBlob)
			{

				ID3D11ShaderReflection* shaderReflection = GetShaderReflection(shaderBlob);

				D3D11_SHADER_DESC shaderDesc;
				shaderReflection->GetDesc(&shaderDesc);
				HRESULT hr;
				for (int i = 0; i < shaderDesc.ConstantBuffers; i++)
				{
					D3D11_SHADER_BUFFER_DESC bufferDesc;
					ID3D11ShaderReflectionConstantBuffer* constantBuffer = shaderReflection->GetConstantBufferByIndex(i);
					hr = constantBuffer->GetDesc(&bufferDesc);
					

					D3D11_SHADER_INPUT_BIND_DESC bindDesc;
					hr = shaderReflection->GetResourceBindingDescByName(bufferDesc.Name, &bindDesc);

					for (int j = 0; j < bufferDesc.Variables; j++)
					{
						ID3D11ShaderReflectionVariable* variable = constantBuffer->GetVariableByIndex(j);
						D3D11_SHADER_VARIABLE_DESC variableDesc;
						variable->GetDesc(&variableDesc);
						std::string name = variableDesc.Name;
					}
				}
			}


			Shader::Shader(std::string name, std::string filePath)
			{
				m_name = name;
				m_filePath = filePath;

				m_data.vs = Compile(filePath, "vs_5_0", "VSMain");
				m_data.ps = Compile(filePath, "ps_5_0", "PSMain");

				if(m_data.vs)
					ThomasCore::GetDevice()->CreateVertexShader(m_data.vs->GetBufferPointer(), m_data.vs->GetBufferSize(), NULL, &m_data.vertexShader);
				if(m_data.ps)
					ThomasCore::GetDevice()->CreatePixelShader(m_data.ps->GetBufferPointer(), m_data.ps->GetBufferSize(), NULL, &m_data.pixelShader);
				//ThomasCore::GetDevice()->CreateVertexShader(m_data.vs->GetBufferPointer(), m_data.vs->GetBufferSize(), NULL, &m_data.vertexShader);

				//ShaderManager::AddShader(this);

			}

			Shader::~Shader()
			{
				if(m_data.vs)
					m_data.vertexShader->Release();
				if(m_data.ps)
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
			bool Shader::BindBuffer(ID3D11Buffer * resource, ResourceType type)
			{
				if (s_currentBoundShader == this)
				{
					return BindBuffer(resource, (int)type);
				}
				return false;
			}
			bool Shader::BindBuffer(ID3D11Buffer * resource, int slot)
			{
				if (s_currentBoundShader == this)
				{
					if (m_data.vs)
						ThomasCore::GetDeviceContext()->VSSetConstantBuffers(slot, 1, &resource);
					if (m_data.ps)
						ThomasCore::GetDeviceContext()->PSSetConstantBuffers(slot, 1, &resource);
					return true;
				}
				return false;
			}
			bool Shader::BindTextures(ID3D11ShaderResourceView * texture, int slot)
			{
				if (s_currentBoundShader == this)
				{
					if (m_data.vs)
						ThomasCore::GetDeviceContext()->VSSetShaderResources(slot, 1, &texture);
					if (m_data.ps)
						ThomasCore::GetDeviceContext()->PSSetShaderResources(slot, 1, &texture);
					return true;
				}
				return false;
			}
			bool Shader::BindTextureSampler(ID3D11SamplerState * sampler, int slot)
			{
				if (s_currentBoundShader == this)
				{
					if (m_data.vs)
						ThomasCore::GetDeviceContext()->VSSetSamplers(slot, 1, &sampler);
					if (m_data.ps)
						ThomasCore::GetDeviceContext()->PSSetSamplers(slot, 1, &sampler);
					return true;
				}
				return false;
			}
			Shader * Shader::GetCurrentBoundShader()
			{
				return s_currentBoundShader;
			}
		}
	}
}