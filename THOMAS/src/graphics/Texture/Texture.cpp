#include "Texture.h"
#include "../../ThomasCore.h"

namespace thomas
{
	namespace graphics
	{
		Texture::Data Texture::s_data;
		std::vector<Texture*> Texture::s_loadedTextures;
		Texture* Texture::CreateTexture(std::string fileName)
		{
			for (int i = 0; i < s_loadedTextures.size(); ++i)
			{
				if (fileName == s_loadedTextures[i]->GetFileName())
					return s_loadedTextures[i];
			}
			ID3D11ShaderResourceView* textureView;
			ID3D11Resource* texture;
			if (utils::D3d::LoadTextureFromFile(ThomasCore::GetDevice(), ThomasCore::GetDeviceContext(), fileName, &texture, &textureView, NULL))
			{
				Texture tex(fileName, textureView, texture);
				s_loadedTextures.push_back(&tex);
				return &tex;
			}
			return NULL;
		}

		std::string Texture::GetFileName()
		{
			return s_data.fileName;
		}

		ID3D11Resource * Texture::GetTexture()
		{
			return s_data.texture;
		}

		ID3D11ShaderResourceView * Texture::GetTextureView()
		{
			return s_data.textureView;
		}
		Texture::Texture(std::string fileName, ID3D11ShaderResourceView * textureView,
			ID3D11Resource * texture)
		{
			s_data.fileName = fileName;
			s_data.texture = texture;
			s_data.textureView = textureView;
		}
		void Texture::Destroy()
		{
			for (int i = 0; i < s_loadedTextures.size(); ++i)
			{
				s_loadedTextures[i]->s_data.texture->Release();
				s_loadedTextures[i]->s_data.textureView->Release();
			}
		}

	}
}