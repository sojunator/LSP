#pragma once
#include <map>
#include "../utils/Math.h"
#include "Shader.h"
#include "../Window.h"
#include <ft2build.h>
#include FT_FREETYPE_H 

namespace thomas
{
	namespace graphics
	{
		//class Texture;

		class TextRenderer
		{
		public:
			TextRenderer();
			~TextRenderer();
			void Load(std::string font, int fontSize);
			void RenderText(std::string text, float x, float y, float scaleFactor, math::Vector3 color);

		private:
			struct Character
			{
				ID3D11Texture2D* texture;
				math::Vector2 size;
				math::Vector2 offset;
				int advance;
			};

			struct textData
			{
				ID3D11Buffer *vertexBuffer, *indexBuffer, *constantBuffer;
				int vertexCount, indexCount;
				ID3D11DepthStencilState* depthStencilState;
				ID3D11RasterizerState* rasterizerState;
				Shader* shader;
				//Texture* texture;
			};
			
		private:
			std::map <char, Character> m_characters;
		};
	}
}

