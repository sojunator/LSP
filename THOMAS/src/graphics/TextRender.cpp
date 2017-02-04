#include "TextRender.h"

namespace thomas
{
	namespace graphics
	{
		TextRender::TextRender(std::string font)
		{
			std::wstring holder = std::wstring(font.begin(), font.end());
			const wchar_t* result = holder.c_str();

			m_font = std::make_unique<DirectX::SpriteFont>(ThomasCore::GetDevice(), result);
			m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(ThomasCore::GetDeviceContext());
		}

		TextRender::~TextRender()
		{
			m_font.reset();
			m_spriteBatch.reset();
		}

		void TextRender::RenderText(std::string output, float posX, float posY, float scale, float rotation,
									math::Vector3 color, bool dropShadow, bool outline)
		{
			SetFontPosX(posX);
			SetFontPosY(posY);

			std::wstring holder = std::wstring(output.begin(), output.end());
			const wchar_t* result = holder.c_str();

			m_spriteBatch->Begin();

			math::Vector2 origin = m_font->MeasureString(result);
			origin.operator/=(2.f);

			if (dropShadow)
			{
				m_font->DrawString(m_spriteBatch.get(), result,
					m_fontPos + math::Vector2(1.f, 1.f), DirectX::Colors::Black, rotation, origin, scale);
				m_font->DrawString(m_spriteBatch.get(), result,
					m_fontPos + math::Vector2(-1.f, 1.f), DirectX::Colors::Black, rotation, origin, scale);
			}

			if (outline)
			{
				m_font->DrawString(m_spriteBatch.get(), result,
					m_fontPos + math::Vector2(-1.f, -1.f), DirectX::Colors::Black, rotation, origin, scale);
				m_font->DrawString(m_spriteBatch.get(), result,
					m_fontPos + math::Vector2(1.f, -1.f), DirectX::Colors::Black, rotation, origin, scale);
			}

			m_font->DrawString(m_spriteBatch.get(), result, GetFontPos(), color, rotation, origin, scale);

			m_spriteBatch->End();
		}

		void TextRender::SetFontPosX(float posX)
		{
			m_fontPos.x = posX;
		}

		void TextRender::SetFontPosY(float posY)
		{
			m_fontPos.y = posY;
		}

		math::Vector2 TextRender::GetFontPos()
		{
			return m_fontPos;
		}
	}
}