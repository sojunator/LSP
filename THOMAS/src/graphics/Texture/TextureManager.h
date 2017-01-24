#pragma once
#include <vector>
#include <string>
#include "../../Common.h"
#include "Texture.h"

// STATIC

namespace thomas
{
	namespace graphics
	{
		namespace THOMAS_API texture
		{
			class Texture;
			class TextureManager
			{
			public:
				static bool AddTexture(Texture* texture);
				static Texture* GetTexture(std::string name);
			private:
				static std::vector<Texture> s_loadedTextures;
			};
		}
	}
}