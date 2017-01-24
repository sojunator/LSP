#include "Texture.h"

namespace thomas
{
	namespace graphics
	{
		namespace texture
		{
			std::string graphics::texture::Texture::GetName()
			{
				return m_name;
			}

			std::string graphics::texture::Texture::GetFilePath()
			{
				return m_filePath;
			}

			bool graphics::texture::Texture::Initialize(std::string name, std::string path, int width, int height)
			{

				return false;
			}
		}
	}
}