#pragma once
#include "../utils/Math.h"
#include "../ThomasCore.h"
#include <wrl.h>
#include "../../packages/directxtk_desktop_2015.2016.12.5.1/build/native/include/SpriteBatch.h"
#include "../utils/directXTK/WICTextureLoader.h"

namespace thomas
{
	namespace graphics
	{
		class Sprite
		{
		public:
			static bool LoadTexture(std::string texture);
			static void Destroy();
			static bool Initialize();
			static void SetImagePosX(float posX);
			static void SetImagePosY(float posY);
			static void RenderImage(float posX, float posY, float scale);
			static math::Vector2 GetImagePos();

		private:
			static Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> s_texture;
			static Microsoft::WRL::ComPtr<ID3D11Resource> s_resource;
			static Microsoft::WRL::ComPtr<ID3D11Texture2D> s_image;
			static std::unique_ptr<DirectX::SpriteBatch> s_spriteBatch;
			static DirectX::SimpleMath::Vector2 s_screenPos;
			static DirectX::SimpleMath::Vector2 s_origin;

		};
	}
}

