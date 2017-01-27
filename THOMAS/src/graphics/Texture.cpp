#include "Texture.h"
#include "Shader.h"
#include "../ThomasCore.h"
#include  "../utils/AssimpLoader.h"
namespace thomas
{
	namespace graphics
	{
		std::vector<Texture*> Texture::s_loadedTextures;
		Texture::SamplerStates Texture::s_samplerStates;
		bool Texture::Init()
		{
			LOG("Creating Texture samplers");
			return CreateTextureSamplers();
		}
		Texture* Texture::CreateTexture(int mappingMode, TextureType type, std::string path)
		{
			for (int i = 0; i < s_loadedTextures.size(); ++i)
			{
				if (s_loadedTextures[i]->GetName() == path)
					return s_loadedTextures[i];
			}

			Texture* texture = new Texture(mappingMode, type, path);
			if (texture)
				s_loadedTextures.push_back(texture);
			return texture;
		}

		std::string Texture::GetName()
		{
			return m_name;
		}

		ID3D11Resource * Texture::GetTexture()
		{
			return m_data.texture;
		}

		ID3D11ShaderResourceView * Texture::GetTextureView()
		{
			return m_data.textureView;
		}
		bool Texture::Initialized()
		{
			return m_initialized;
		}
		bool Texture::Bind()
		{
			Shader::GetCurrentBoundShader()->BindTextureSampler(m_samplerState, (int)m_textureType);
			return Shader::GetCurrentBoundShader()->BindTextures(m_data.textureView, (int)m_textureType);
		}
		bool Texture::Unbind()
		{
			return Shader::GetCurrentBoundShader()->BindTextures(NULL, (int)m_textureType);
		}
		Texture::Texture(int mappingMode, TextureType type, std::string path)
		{

			m_textureType = type;
			m_name = path;
			m_initialized = utils::D3d::LoadTextureFromFile(ThomasCore::GetDevice(), ThomasCore::GetDeviceContext(), path, m_data.texture, m_data.textureView);
			if (m_initialized)
				SetTextureSampler(mappingMode);

		}
		bool Texture::CreateTextureSamplers()
		{
			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;


			HRESULT result;

			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			result = ThomasCore::GetDevice()->CreateSamplerState(&samplerDesc, &s_samplerStates.WRAP);


			if (result)
			{
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
				result = ThomasCore::GetDevice()->CreateSamplerState(&samplerDesc, &s_samplerStates.CLAMP);
			}

			if (result)
			{
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
				result = ThomasCore::GetDevice()->CreateSamplerState(&samplerDesc, &s_samplerStates.DECAL);
			}

			if (result)
			{
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
				result = ThomasCore::GetDevice()->CreateSamplerState(&samplerDesc, &s_samplerStates.MIRROR);
			}

			return result == S_OK;
		}
		void Texture::SetTextureSampler(int textureMode)
		{
			switch (textureMode)
			{
			case aiTextureMapMode_Wrap:
				m_samplerState = s_samplerStates.WRAP;
				break;
			case aiTextureMapMode_Clamp:
				m_samplerState = s_samplerStates.CLAMP;
				break;
			case aiTextureMapMode_Decal:
				m_samplerState = s_samplerStates.DECAL;
				break;
			case aiTextureMapMode_Mirror:
				m_samplerState = s_samplerStates.MIRROR;
				break;
			default:
				m_samplerState = s_samplerStates.WRAP;
				break;
			}
		}
		void Texture::Destroy()
		{
			for (int i = 0; i < s_loadedTextures.size(); ++i)
			{
				s_loadedTextures[i]->m_data.texture->Release();
				s_loadedTextures[i]->m_data.textureView->Release();
			}
		}

	}
}