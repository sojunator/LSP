#pragma once
#include "../utils/Math.h"
#include "../Window.h"
#include "../ThomasCore.h"
#include "../../../packages/directxtk_desktop_2015.2016.12.5.1/build/native/include/SpriteBatch.h"
#include "../../../packages/directxtk_desktop_2015.2016.12.5.1/build/native/include/SpriteFont.h"

namespace thomas
{
	namespace graphics
	{
		class TextRender
		{
		private:
			void SetFontPosX(float posX);
			void SetFontPosY(float posY);
			math::Vector2 GetFontPos();

		public:
			TextRender(std::wstring font);
			~TextRender();
			void RenderText(std::wstring output, float posX, float posY, float r, float g, float b);

		private:
			std::unique_ptr<DirectX::SpriteFont> m_font;
			math::Vector2 m_fontPos;
			std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		};
	}
}

