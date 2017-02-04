#include "TextRender.h"

namespace thomas
{
	namespace graphics
	{
		std::unique_ptr<DirectX::SpriteFont> TextRender::s_font;
		math::Vector2 TextRender::s_fontPos;
		std::unique_ptr<DirectX::SpriteBatch> TextRender::s_spriteBatch;

		void TextRender::RenderText(std::string output, float posX, float posY, float scale, float rotation,
									math::Vector3 color, bool dropShadow, bool outline)
		{
			SetFontPosX(posX);
			SetFontPosY(posY);

			std::wstring holder = std::wstring(output.begin(), output.end());
			const wchar_t* result = holder.c_str();

			s_spriteBatch->Begin();

			math::Vector2 origin = s_font->MeasureString(result);
			origin.operator/=(2.f);

			if (dropShadow)
			{
				s_font->DrawString(s_spriteBatch.get(), result,
					s_fontPos + math::Vector2(1.f, 1.f), DirectX::Colors::Black, rotation, origin, scale);
				s_font->DrawString(s_spriteBatch.get(), result,
					s_fontPos + math::Vector2(-1.f, 1.f), DirectX::Colors::Black, rotation, origin, scale);
			}

			if (outline)
			{
				s_font->DrawString(s_spriteBatch.get(), result,
					s_fontPos + math::Vector2(-1.f, -1.f), DirectX::Colors::Black, rotation, origin, scale);
				s_font->DrawString(s_spriteBatch.get(), result,
					s_fontPos + math::Vector2(1.f, -1.f), DirectX::Colors::Black, rotation, origin, scale);
			}

			s_font->DrawString(s_spriteBatch.get(), result, GetFontPos(), color, rotation, origin, scale);

			s_spriteBatch->End();
		}

		void TextRender::SetFontPosX(float posX)
		{
			s_fontPos.x = posX;
		}

		void TextRender::SetFontPosY(float posY)
		{
			s_fontPos.y = posY;
		}

		bool TextRender::LoadFont(std::string font)
		{
			std::wstring holder = std::wstring(font.begin(), font.end());
			const wchar_t* result = holder.c_str();

			s_font = std::make_unique<DirectX::SpriteFont>(ThomasCore::GetDevice(), result);

			if (!s_font)
			{
				LOG("Failed to load font for text, check if the directory is correct.");
				return false;
			}

			s_spriteBatch = std::make_unique<DirectX::SpriteBatch>(ThomasCore::GetDeviceContext());

			if (!s_spriteBatch)
			{
				LOG("Failed to initialize spriteBatch");
				return false;
			}
			return true;
		}

		math::Vector2 TextRender::GetFontPos()
		{
			return s_fontPos;
		}

		void TextRender::Destroy()
		{
			s_font.reset();
			s_spriteBatch.reset();
		}
	}
}