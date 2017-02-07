#pragma once
#include "../utils/Math.h"
#include "../ThomasCore.h"
#include <wrl.h>
#include "../../../DirectXTK-dec2016/Inc/SpriteBatch.h"
#include "../../../DirectXTK-dec2016/Inc/WICTextureLoader.h"
#include "../object/component/SpriteComponent.h"
#include <map>

namespace thomas
{
	namespace graphics
	{
		class Sprite
		{
		public:
			static bool LoadTexture(std::string name, std::string texture);
			static void Destroy();
			static bool Initialize();
			static void SetImagePosX(float posX);
			static void SetImagePosY(float posY);
			static void RenderImage(std::string name, float posX, float posY, float scale);
			static void RenderImage(object::component::SpriteComponent* sprite);
			static math::Vector2 GetImagePos();

		private:
			static std::map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> s_texture;
			static std::unique_ptr<DirectX::SpriteBatch> s_spriteBatch;
			static DirectX::SimpleMath::Vector2 s_screenPos;
			static DirectX::SimpleMath::Vector2 s_origin;
		};
	}
}

