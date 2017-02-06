#include "Sprite.h"

namespace thomas
{
	namespace graphics
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Sprite::s_texture;
		Microsoft::WRL::ComPtr<ID3D11Resource> Sprite::s_resource;
		std::unique_ptr<DirectX::SpriteBatch> Sprite::s_spriteBatch;
		DirectX::SimpleMath::Vector2 Sprite::s_screenPos;
		DirectX::SimpleMath::Vector2 Sprite::s_origin;

		bool Sprite::LoadTexture(std::string texture)
		{
			std::wstring holder = std::wstring(texture.begin(), texture.end());
			const wchar_t* result = holder.c_str();

			HRESULT hr = DirectX::CreateWICTextureFromFile(ThomasCore::GetDevice(), result, s_resource.GetAddressOf(), s_texture.ReleaseAndGetAddressOf());

			if (FAILED(hr))
			{
				LOG("Failed to load " << result << " for GUI");
				return false;
			}

			CD3D11_TEXTURE2D_DESC imageDesc;
			s_image->GetDesc(&imageDesc);

			s_origin.x = float(imageDesc.Width / 2);
			s_origin.y = float(imageDesc.Height / 2);

			return true;
		}

		void Sprite::Destroy()
		{
			s_texture.Reset();
			s_image.Reset();
			s_resource.Reset();
			s_spriteBatch.reset();
		}

		bool Sprite::Initialize()
		{
			s_spriteBatch = std::make_unique<DirectX::SpriteBatch>(ThomasCore::GetDeviceContext());

			if (!s_spriteBatch)
			{
				LOG("Failed to initialize spriteBatch");
				return false;
			}
			return true;
		}

		void Sprite::SetImagePosX(float posX)
		{
			s_screenPos.x = posX;
		}

		void Sprite::SetImagePosY(float posY)
		{
			s_screenPos.y = posY;
		}

		void Sprite::RenderImage(float posX, float posY, float scale)
		{
			SetImagePosX(posX);
			SetImagePosY(posY);

			s_spriteBatch->Begin();

			s_spriteBatch->Draw(s_texture.Get(), GetImagePos(), nullptr, DirectX::Colors::White,
				0.f, s_origin, scale);

			s_spriteBatch->End();
		}

		math::Vector2 Sprite::GetImagePos()
		{
			return s_screenPos;
		}
	}
}
