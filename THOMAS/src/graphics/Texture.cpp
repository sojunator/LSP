#include "Texture.h"
#include "Shader.h"
#include "../ThomasCore.h"

namespace thomas
{
	namespace graphics
	{
		std::vector<Texture*> Texture::s_loadedTextures;
		Texture* Texture::CreateTexture(TextureType type, std::string path)
		{
			for (int i = 0; i < s_loadedTextures.size(); ++i)
			{
				if (s_loadedTextures[i]->GetName() == path)
					return s_loadedTextures[i];
			}
			
			Texture* texture = new Texture(type, path);
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
		bool Texture::Bind()
		{
			return Shader::GetCurrentBoundShader()->BindTextures(m_data.textureView, (int)m_textureType);
		}
		bool Texture::Unbind()
		{
			return Shader::GetCurrentBoundShader()->BindTextures(NULL, (int)m_textureType);
		}
		Texture::Texture(TextureType type, std::string path)
		{
			m_textureType = type;
			m_name = path;
			utils::D3d::LoadTextureFromFile(ThomasCore::GetDevice(), ThomasCore::GetDeviceContext(), path, m_data.texture, m_data.textureView);

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