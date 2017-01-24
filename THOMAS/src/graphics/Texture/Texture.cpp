#include "Texture.h"
#include "../../ThomasCore.h"

namespace thomas
{
	namespace graphics
	{
		namespace texture
		{
			int Texture::LoadTexture(std::string fileName)
			{
				ID3D11ShaderResourceView* textureView;
				ID3D11Resource* texture;
				if(utils::D3d::LoadTextureFromFile(ThomasCore::GetDevice(), ThomasCore::GetDeviceContext(), fileName, &texture, &textureView, NULL))
					//do push_back

				return ;
			}

			std::string Texture::GetFilePath(int index)
			{
				return s_loadedTextures[index]->m_data.filePath;
			}

			ID3D11Resource * Texture::getTexture(int index)
			{
				return s_loadedTextures[index]->m_data.texture;
			}

			ID3D11ShaderResourceView * Texture::getTextureView(int index)
			{
				return s_loadedTextures[index]->m_data.textureView;
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
}