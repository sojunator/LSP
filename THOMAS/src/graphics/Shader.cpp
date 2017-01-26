#include "Shader.h"
#include "../ThomasCore.h"
#include <AtlBase.h>
#include <atlconv.h>
namespace thomas
{
	namespace graphics
	{

		Shader* Shader::s_currentBoundShader;
		std::vector<Shader*> Shader::s_loadedShaders;

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

		bool Shader::CreateInputLayout(InputLayouts layout)
		{

			std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc;

			switch (layout)
			{
			case InputLayouts::STANDARD:
				layoutDesc =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
				break;
			default:
				return false;
				break;
			}


			HRESULT result = ThomasCore::GetDevice()->CreateInputLayout(&layoutDesc.front(), layoutDesc.size(), m_data.vs->GetBufferPointer(), m_data.vs->GetBufferSize(), &m_data.inputLayout);

			if (FAILED(result))
			{
				LOG("ERROR::FAILED TO CREATE INPUT LAYOUT");
				return false;
			}

			return true;
		}


		Shader::Shader(std::string name, std::string filePath, InputLayouts inputLayout)
		{
			m_name = name;
			m_filePath = filePath;

			m_data.vs = Compile(filePath, "vs_5_0", "VSMain");
			m_data.ps = Compile(filePath, "ps_5_0", "PSMain");

			if (m_data.vs)
				ThomasCore::GetDevice()->CreateVertexShader(m_data.vs->GetBufferPointer(), m_data.vs->GetBufferSize(), NULL, &m_data.vertexShader);
			if (m_data.ps)
				ThomasCore::GetDevice()->CreatePixelShader(m_data.ps->GetBufferPointer(), m_data.ps->GetBufferSize(), NULL, &m_data.pixelShader);
			//ThomasCore::GetDevice()->CreateVertexShader(m_data.vs->GetBufferPointer(), m_data.vs->GetBufferSize(), NULL, &m_data.vertexShader);

			CreateInputLayout(inputLayout);

		}

		Shader::~Shader()
		{
			Unbind();
			if (m_data.vs)
			{
				m_data.vertexShader->Release();
				m_data.vs->Release();
			}

			if (m_data.ps)
			{
				m_data.pixelShader->Release();
				m_data.ps->Release();
			}

			m_data.inputLayout->Release();
		}

		bool Shader::Destroy() {
			for (int i = 0; i < s_loadedShaders.size(); i++)
			{
				delete s_loadedShaders[i];
			}
			return true;
		}

		bool Shader::Bind()
		{
			s_currentBoundShader = this;
			if(m_data.vs)
				ThomasCore::GetDeviceContext()->VSSetShader(m_data.vertexShader, NULL, 0);

			if(m_data.ps)
				ThomasCore::GetDeviceContext()->PSSetShader(m_data.pixelShader, NULL, 0);


			ThomasCore::GetDeviceContext()->IASetInputLayout(m_data.inputLayout);
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
			return m_name;
		}
		std::string Shader::GetFilePath()
		{
			return m_filePath;
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
		bool Shader::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY type)
		{
			if (s_currentBoundShader == this)
				ThomasCore::GetDeviceContext()->IASetPrimitiveTopology(type);
			return true;
		}
		bool Shader::BindVertexBuffer(ID3D11Buffer * vertexBuffer, UINT stride, UINT offset = 0)
		{
			if (s_currentBoundShader == this)
				ThomasCore::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
			return true;
		}
		bool Shader::BindIndexBuffer(ID3D11Buffer * indexBuffer)
		{
			if (s_currentBoundShader == this)
				ThomasCore::GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
			return true;
		}

		
		Shader * Shader::CreateShader(std::string name, std::string filePath, InputLayouts inputLayout)
		{
			Shader* shader = new Shader(name, filePath, inputLayout);
			if (shader)
				s_loadedShaders.push_back(shader);
			return shader;
		}
		Shader * Shader::GetCurrentBoundShader()
		{
			return s_currentBoundShader;
		}
		Shader * Shader::GetShader(std::string name)
		{
			for (int i = 0; i < s_loadedShaders.size(); i++)
			{
				if (s_loadedShaders[i]->GetName() == name)
					return s_loadedShaders[i];
			}
			return NULL;
		}
	}

}