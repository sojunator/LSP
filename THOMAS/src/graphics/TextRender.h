#pragma once
#include "../utils/Math.h"
#include "../ThomasCore.h"
#include <map>
#include "../../../DirectXTK-dec2016/Inc/SpriteBatch.h"
#include "../../../DirectXTK-dec2016/Inc/SpriteFont.h"
#include "../../../DirectXTK-dec2016/Inc/CommonStates.h"
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
			static std::unique_ptr<DirectX::CommonStates> s_states;
		};
	}
}

