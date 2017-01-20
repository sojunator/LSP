#pragma once
#include "../../Common.h"
#include <string>
namespace thomas {
	namespace graphics {
		namespace shader {
			class THOMAS_API Shader {
			private:
			public:
				static Shader CreateFromFile(std::string name, std::string filePath);
				bool Bind();
				bool Unbind();
				std::string GetName();
				std::string GetFilePath();
				static Shader* GetCurrentBoundShader();


			private:
				std::string m_name;
				std::string m_filePath;
				static Shader* s_currentBoundShader;
			};
		}
	}
}