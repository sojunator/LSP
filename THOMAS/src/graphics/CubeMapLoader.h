#pragma once
#include "Texture.h"

namespace thomas
{
	namespace graphics
	{
		class CubeMapLoader
		{
		private:

		public:
			CubeMapLoader(std::string path);
			~CubeMapLoader();
			std::string GetName();
			CubeMapLoader* CreateCubeMapTexture(std::string top, std::string left, std::string front, std::string right, std::string back, std::string bottom); //STATIC

		private:
			/*struct CubeMapTextureData
			{
				ID3D11ShaderResourceView* textureView;
				ID3D11Resource* srcTex[6];
				ID3D11Texture2D* cubeTexture;
			};*/

			std::string m_name;
			//CubeMapTextureData m_data;
			bool m_initialized;
			static std::vector<CubeMapLoader*> s_loadedTextures;
		};
	}
}
