#pragma once

#include <string>
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
				Texture();
				~Texture();

				std::string GetName();
				std::string GetFilePath();

				bool Initialize(std::string name, std::string path, int width, int height);
			private:
				std::string m_name;
				std::string m_filePath;
				ID3D11ShaderResourceView* m_textureView;
				ID3D11Texture2D* m_texture;
			};
		}
	}
}