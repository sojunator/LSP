#include "CubeMapLoader.h"

namespace thomas
{
	namespace graphics
	{
		std::vector<CubeMapLoader*> s_loadedTextures;

		CubeMapLoader::CubeMapLoader(std::string path) 
		{
			//m_name = path;
			//m_initialized = utils::D3d::LoadTextureFromFile(ThomasCore::GetDevice(), ThomasCore::GetDeviceContext(), path, m_data.texture, m_data.textureView);
			//if (m_initialized)
				//SetTextureSampler(mappingMode);
		}

		CubeMapLoader::~CubeMapLoader()
		{
		}

		std::string CubeMapLoader::GetName()
		{
			return m_name;
		}

		CubeMapLoader * CubeMapLoader::CreateCubeMapTexture(std::string top, std::string left, std::string front, std::string right, std::string back, std::string bottom)
		{
			ID3D11ShaderResourceView* srv = 0;
			ID3D11Resource* srcTex[6];
			
			std::vector <std::string> myTextures;
			myTextures.push_back(right);
			myTextures.push_back(left);
			myTextures.push_back(top);
			myTextures.push_back(bottom);
			myTextures.push_back(back);
			myTextures.push_back(front);

			// Each element in the texture array has the same format/dimensions.
			D3D11_TEXTURE2D_DESC texElementDesc;
			((ID3D11Texture2D*)srcTex[0])->GetDesc(&texElementDesc);

			D3D11_TEXTURE2D_DESC texArrayDesc;
			texArrayDesc.Width = texElementDesc.Width;
			texArrayDesc.Height = texElementDesc.Height;
			texArrayDesc.MipLevels = texElementDesc.MipLevels;
			texArrayDesc.ArraySize = 6;
			texArrayDesc.Format = texElementDesc.Format;
			texArrayDesc.SampleDesc.Count = 1;
			texArrayDesc.SampleDesc.Quality = 0;
			texArrayDesc.Usage = D3D11_USAGE_DEFAULT;
			texArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			texArrayDesc.CPUAccessFlags = 0;
			texArrayDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

			ID3D11Texture2D* texArray = 0;
			if (FAILED(ThomasCore::GetDevice()->CreateTexture2D(&texArrayDesc, 0, &texArray)))
				return false;

			// Copy individual texture elements into texture array.
			//ThomasCore::GetDevice()->GetImmediateContext(&ThomasCore::GetDeviceContext());
			D3D11_BOX sourceRegion;

			//Mip levels of the texture
			for (unsigned int x = 0; x < 6; x++)
			{
				for (unsigned int mipLevel = 0; mipLevel < texArrayDesc.MipLevels; mipLevel++)
				{
					sourceRegion.left = 0;
					sourceRegion.right = (texArrayDesc.Width >> mipLevel);
					sourceRegion.top = 0;
					sourceRegion.bottom = (texArrayDesc.Height >> mipLevel);
					sourceRegion.front = 0;
					sourceRegion.back = 1;

					if (sourceRegion.bottom == 0 || sourceRegion.right == 0)
						break;

					ThomasCore::GetDeviceContext()->CopySubresourceRegion(texArray, D3D11CalcSubresource(mipLevel, x, texArrayDesc.MipLevels), 0, 0, 0, srcTex[x], mipLevel, &sourceRegion);
				}
			}

			// Create a resource view to the texture array.
			D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
			viewDesc.Format = texArrayDesc.Format;
			viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			viewDesc.TextureCube.MostDetailedMip = 0;
			viewDesc.TextureCube.MipLevels = texArrayDesc.MipLevels;

			if (FAILED(ThomasCore::GetDevice()->CreateShaderResourceView(texArray, &viewDesc, &srv)))
				return false;

			/*for (unsigned int i = 0; i < myTextures.size(); i++)
			{
				m_initialized = utils::D3d::LoadTextureFromFile(ThomasCore::GetDevice(), ThomasCore::GetDeviceContext(), myTextures[i], m_data.texture, m_data.textureView);
			}*/

			/*for (int i = 0; i < s_loadedTextures.size(); ++i)
			{
				if (s_loadedTextures[i]->GetName() == path)
					return s_loadedTextures[i];
			}

			CubeMapLoader* cubeMapTexture = new CubeMapLoader(path);
			if (cubeMapTexture)
				s_loadedTextures.push_back(cubeMapTexture);
			return cubeMapTexture;*/
		}
	
	}
}
