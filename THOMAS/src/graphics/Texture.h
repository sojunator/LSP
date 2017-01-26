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

			//represents texture slot
			enum class TextureType
			{
				DIFFUSE = 0,
				SPECULAR = 1,
				NORMAL = 2
			};


		private:
			Texture(TextureType type, std::string path);
		public:



			static Texture* CreateTexture(TextureType type, std::string path);
			std::string GetName();
			ID3D11Resource* GetTexture();
			ID3D11ShaderResourceView* GetTextureView();

			bool Bind();
			bool Unbind();

			static void Destroy();
		private:
			struct TextureData
			{
				ID3D11ShaderResourceView* textureView;
				ID3D11Resource* texture;
			};

			std::string m_name;
			TextureData m_data;
			static std::vector<Texture*> s_loadedTextures;

			TextureType m_textureType;
		};
	}

}