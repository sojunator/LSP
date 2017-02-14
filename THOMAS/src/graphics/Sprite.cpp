#include "Sprite.h"

namespace thomas
{
	namespace graphics
	{
		std::map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> Sprite::s_texture;
		std::unique_ptr<DirectX::SpriteBatch> Sprite::s_spriteBatch;
		DirectX::SimpleMath::Vector2 Sprite::s_screenPos;
		DirectX::SimpleMath::Vector2 Sprite::s_origin;
		std::unique_ptr<DirectX::CommonStates> Sprite::s_states;
		UINT Sprite::s_imageWidth;
		UINT Sprite::s_imageHeight;

		bool Sprite::LoadTexture(std::string name, std::string texture)
		{
			std::wstring holder = std::wstring(texture.begin(), texture.end());
			const wchar_t* result = holder.c_str();

			Microsoft::WRL::ComPtr<ID3D11Resource> resource;
			HRESULT hr = DirectX::CreateWICTextureFromFile(ThomasCore::GetDevice(), result, resource.GetAddressOf(), s_texture[name].ReleaseAndGetAddressOf());

			if (FAILED(hr))
			{
				LOG("Failed to load " << result << " for GUI");
				return false;
			}

			Microsoft::WRL::ComPtr<ID3D11Texture2D> image;
			resource.As(&image);

			CD3D11_TEXTURE2D_DESC imageDesc;
			image->GetDesc(&imageDesc);
			
			s_imageWidth = imageDesc.Width;
			s_imageHeight = imageDesc.Height;

			s_origin.x = 0;
			s_origin.y = 0;

			return true;
		}

		void Sprite::Destroy()
		{
			std::map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>::iterator itr;
			itr = s_texture.begin();

			while (itr != s_texture.end())
			{
				itr = s_texture.erase(itr);
			}
			s_spriteBatch.reset();
			s_states.reset();
		}

		bool Sprite::Initialize()
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

		UINT Sprite::GetImageWidth()
		{
			return s_imageWidth;
		}

		UINT Sprite::GetImageHeight()
		{
			return s_imageHeight;
		}

		void Sprite::SetImagePosX(float posX)
		{
			s_screenPos.x = posX;
		}

		void Sprite::SetImagePosY(float posY)
		{
			s_screenPos.y = posY;
		}

		void Sprite::RenderImage(std::string name, float posX, float posY, float scale)
		{
			SetImagePosX(posX);
			SetImagePosY(posY);
			
			s_spriteBatch->Begin();
						
			s_spriteBatch->Draw(s_texture[name].Get(), GetImagePos(), nullptr, DirectX::Colors::White,
				0.f, s_origin, scale);

			s_spriteBatch->End();
		}

		void Sprite::RenderImage(object::component::SpriteComponent * sprite)
		{
			RenderImage(sprite->GetSignature(), sprite->GetPosition().x, sprite->GetPosition().y, sprite->GetScale());
		}

		void Sprite::PickImage(object::component::SpriteComponent * sprite)
		{
			//Only in a certain state, like menu
			Input::SetMouseMode(Input::MouseMode::POSITION_ABSOLUTE);
			math::Vector2 mousePos = Input::GetMousePosition();

			//Construct boundaries
			float xLeft = sprite->GetPosition().x;
			float xRight = sprite->GetPosition().x + sprite->GetWidth();
			float yTop = sprite->GetPosition().y;
			float yDown = sprite->GetPosition().y + sprite->GetHeight();

			if (mousePos.x >= xLeft && mousePos.x <= xRight && mousePos.y <= yDown && mousePos.y >= yTop)
			{
				std::cout << "Yes" << std::endl;
			}
			else
				std::cout << "No" << std::endl;
		}

		math::Vector2 Sprite::GetImagePos()
		{
			return s_screenPos;
		}
	}
}
