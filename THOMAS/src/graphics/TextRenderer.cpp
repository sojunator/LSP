#include "TextRenderer.h"

namespace thomas
{
	namespace graphics
	{

		TextRenderer::TextRenderer()
		{
		}


		TextRenderer::~TextRenderer()
		{
		}

		void TextRenderer::Load(std::string font, int fontSize)
		{
			m_characters.clear();

			FT_Library ft;
			if (FT_Init_FreeType(&ft))
			{
				LOG("Error initializing Freetype library");
			}

			FT_Face face;
			if (FT_New_Face(ft, font.c_str(), 0, &face))
			{
				LOG("Error loading freetype font");
			}

			FT_Set_Pixel_Sizes(face, 0, fontSize);

			//Unpack alignment?
			for (byte c = 0; c < 128; c++)
			{
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					LOG("Error loading freetype glyph");
				}

				ID3D11Texture2D* myTex;
				D3D11_TEXTURE2D_DESC desc;

				desc.Width = face->glyph->bitmap.width;
				desc.Width = face->glyph->bitmap.rows;
				desc.Format = DXGI_FORMAT_R8_UNORM;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.ArraySize = 128;
				desc.MipLevels = 0;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.MiscFlags = 0;

				//Binda textur?

				Character character
				{
					myTex,
					math::Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					math::Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x,
				};
				m_characters.insert(std::pair<char, Character>(c, character));
			}

			//Destroy FREETYPE
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}


		void TextRenderer::RenderText(std::string text, float x, float y, float scaleFactor, math::Vector3 color)
		{

		}

	}
}