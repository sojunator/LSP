#include "TextRender.h"

namespace thomas
{
	namespace graphics
	{
		std::map<std::string, std::unique_ptr<DirectX::SpriteFont>> TextRender::s_fonts;
		math::Vector2 TextRender::s_fontPos;
		std::unique_ptr<DirectX::SpriteBatch> TextRender::s_spriteBatch;
		std::unique_ptr<DirectX::CommonStates> TextRender::s_states;

		void TextRender::RenderText(std::string name, std::string output, float posX, float posY, float scale, float rotation,
									math::Vector3 color, bool dropShadow, bool outline)
		{		
			if (!s_fonts[name])
			{
				LOG(name << " doesn't match any font names.");
			}

			else
			{
				ThomasCore::GetDeviceContext()->OMSetBlendState(s_states->Opaque(), DirectX::Colors::Black, 0xFFFFFFFF);

				SetFontPosX(posX);
				SetFontPosY(posY);

				std::wstring holder = std::wstring(output.begin(), output.end());
				const wchar_t* result = holder.c_str();

				s_spriteBatch->Begin();

				math::Vector2 origin = s_fonts[name]->MeasureString(result);
				origin.operator/=(2.f);

				if (dropShadow)
				{
					s_fonts[name]->DrawString(s_spriteBatch.get(), result,
						s_fontPos + math::Vector2(1.f, 1.f), DirectX::Colors::Black, rotation, origin, scale);
					s_fonts[name]->DrawString(s_spriteBatch.get(), result,
						s_fontPos + math::Vector2(-1.f, 1.f), DirectX::Colors::Black, rotation, origin, scale);
				}

				if (outline)
				{
					s_fonts[name]->DrawString(s_spriteBatch.get(), result,
						s_fontPos + math::Vector2(-1.f, -1.f), DirectX::Colors::Black, rotation, origin, scale);
					s_fonts[name]->DrawString(s_spriteBatch.get(), result,
						s_fontPos + math::Vector2(1.f, -1.f), DirectX::Colors::Black, rotation, origin, scale);
				}

				s_fonts[name]->DrawString(s_spriteBatch.get(), result, GetFontPos(), color, rotation, origin, scale);

				s_spriteBatch->End();

				ThomasCore::GetDeviceContext()->OMSetBlendState(NULL, DirectX::Colors::Black, 0xFFFFFFFF);
			}
		}

		void TextRender::SetFontPosX(float posX)
		{
			s_fontPos.x = posX;
		}

		void TextRender::SetFontPosY(float posY)
		{
			s_fontPos.y = posY;
		}

		void TextRender::SetFontPosCentered()
		{			
			s_fontPos.x = Window::GetWidth() / 2.f;
			s_fontPos.y = Window::GetHeight() / 2.f;		
		}

		bool TextRender::LoadFont(std::string name, std::string font)
		{
			std::wstring holder = std::wstring(font.begin(), font.end());
			const wchar_t* result = holder.c_str();

			s_fonts[name] = std::make_unique<DirectX::SpriteFont>(ThomasCore::GetDevice(), result);

			if (!s_fonts[name])
			{
				LOG("Failed to load font for " << name);
				return false;
			}
			return true;
		}

		bool TextRender::Initialize()
		{
			s_spriteBatch = std::make_unique<DirectX::SpriteBatch>(ThomasCore::GetDeviceContext());
			s_states = std::make_unique<DirectX::CommonStates>(ThomasCore::GetDevice());

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
			std::map<std::string, std::unique_ptr<DirectX::SpriteFont>>::iterator itr;
			itr = s_fonts.begin();

			while (itr != s_fonts.end())
			{
				itr = s_fonts.erase(itr);
			}
			
			s_spriteBatch.reset();
			s_states.reset();
		}

		void TextRender::RenderText(object::component::TextComponent* text)
		{
			RenderText(text->GetFont(), text->GetOutput(), text->GetPosition().x, text->GetPosition().y, text->GetScale(),
				text->GetRotation(), text->GetColor(), text->GetDropshadow(), text->GetOutline());
		}
	}
}