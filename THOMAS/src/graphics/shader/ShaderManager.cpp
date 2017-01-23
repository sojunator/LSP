#include "ShaderManager.h"


namespace thomas
{
	namespace graphics
	{
		namespace shader
		{
			bool thomas::graphics::shader::ShaderManager::AddShader(Shader * shader)
			{
				s_loadedShaders.push_back(shader);
				return true;
			}

			Shader * thomas::graphics::shader::ShaderManager::GetShader(std::string name)
			{
				for (int i = 0; i < s_loadedShaders.size(); i++)
				{
					if (s_loadedShaders[i]->GetName() == name)
						return s_loadedShaders[i];
				}
				return NULL;
			}
		}
	}
}


