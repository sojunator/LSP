#pragma once

#include <string>
#include <vector>
#include "../../Common.h"
#include "../../utils/d3d.h"


namespace thomas
{
	namespace graphics
	{
		namespace texture
		{
			class THOMAS_API Texture
			{
			public:
				static int LoadTexture(std::string path);
				static std::string GetFilePath(int index);
				static ID3D11Resource* getTexture(int index);
				static ID3D11ShaderResourceView* getTextureView(int index);

				static void Destroy();
			private:
				struct Data
				{
					std::string filePath;
					ID3D11ShaderResourceView* textureView;
					ID3D11Resource* texture;
				};

				static Data m_data;
				static std::vector<Texture*> s_loadedTextures;
			};
		}
	}
}