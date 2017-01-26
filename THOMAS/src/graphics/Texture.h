#pragma once

#include <string>
#include <vector>
#include "../Common.h"
#include "../utils/d3d.h"


namespace thomas
{
	namespace graphics
	{
		class THOMAS_API Texture
		{
		private:
			Texture(std::string fileName, ID3D11ShaderResourceView* textureView,
				ID3D11Resource* texture);
		public:
			static Texture* CreateTexture(std::string fileName);
			static std::string GetFileName();
			static ID3D11Resource* GetTexture();
			static ID3D11ShaderResourceView* GetTextureView();


			static void Destroy();
		private:
			struct Data
			{
				std::string fileName;
				ID3D11ShaderResourceView* textureView;
				ID3D11Resource* texture;
			};
			static Data s_data;
			static std::vector<Texture*> s_loadedTextures;
		};
	}

}