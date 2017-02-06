#pragma once
#include "../utils/Math.h"
#include "../ThomasCore.h"
#include <map>
#include "../../packages/directxtk_desktop_2015.2016.12.5.1/build/native/include/SpriteBatch.h"
#include "../../packages/directxtk_desktop_2015.2016.12.5.1/build/native/include/SpriteFont.h"
#include "../object/component/TextComponent.h"

namespace thomas
{
	namespace graphics
	{
		class TextRender
		{
		public:
			static void SetFontPosX(float posX);
			static void SetFontPosY(float posY);
			static void Destroy();
			static void RenderText(object::component::TextComponent* text);
			static void RenderText(std::string name, std::string output, float posX, float posY, float scale, float rotation,
								   math::Vector3 color, bool dropShadow, bool outline);
			static bool LoadFont(std::string name, std::string font);
			static bool Initialize();
			static math::Vector2 GetFontPos();

		private:
			static std::map<std::string, std::unique_ptr<DirectX::SpriteFont>> s_fonts;
			static math::Vector2 s_fontPos;
			static std::unique_ptr<DirectX::SpriteBatch> s_spriteBatch;
		};
	}
}

