#include "TextRender.h"

namespace thomas
{
	namespace graphics
	{

		TextRender::TextRender(std::wstring font)
		{
			m_font = std::make_unique<DirectX::SpriteFont>(ThomasCore::GetDevice(), font.c_str());
			m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(ThomasCore::GetDeviceContext());
		}

		TextRender::~TextRender()
		{
			m_font.reset();
			m_spriteBatch.reset();
		}

		void TextRender::RenderText(std::wstring output, float posX, float posY, float r, float g, float b)
		{
			SetFontPosX(posX);
			SetFontPosY(posY);

			math::Vector3 color = math::Vector3(r, g, b);

			m_spriteBatch->Begin();
			math::Vector2 origin = m_font->MeasureString(output.c_str());

			m_font->DrawString(m_spriteBatch.get(), output.c_str(), GetFontPos(), color, 0.f, origin);

			m_spriteBatch->End();
		}

		void TextRender::SetFontPosX(float posX)
		{
			m_fontPos.x = Window::GetWidth() - posX;
		}

		void TextRender::SetFontPosY(float posY)
		{
			m_fontPos.y = Window::GetHeight() - posY;
		}

		math::Vector2 TextRender::GetFontPos()
		{
			return m_fontPos;
		}
	}
}