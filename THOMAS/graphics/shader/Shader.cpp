#include "Shader.h"

namespace thomas {
	namespace graphics {
		namespace shader {

			Shader* Shader::s_currentBoundShader;


			Shader Shader::CreateFromFile(std::string name, std::string filePath)
			{
				Shader shader;
				shader.m_name = name;
				shader.m_filePath = filePath;
				return shader;
			}

			bool Shader::Bind()
			{
				s_currentBoundShader = this;
				return true;
			}
			bool Shader::Unbind()
			{
				if (s_currentBoundShader != this)
				{
					if(s_currentBoundShader->Unbind())
						return s_currentBoundShader->Bind();
				}
				return false;
			}
			std::string Shader::GetName()
			{
				return std::string();
			}
			std::string Shader::GetFilePath()
			{
				return std::string();
			}
			Shader * Shader::GetCurrentBoundShader()
			{
				return nullptr;
			}
		}
	}
}