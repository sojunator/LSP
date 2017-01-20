#pragma once
#include "../../Common.h"
#include <string>
namespace thomas {
	namespace graphics {
		namespace shader {
			class THOMAS_API Shader {
			private:
			public:
				enum class Swag {
					TEST = 1
				};
				bool Bind();
				bool Unbind();

				std::string GetName();
				std::string GetFileName();
				static Shader* GetCurrentBoundShader();
			private:
				static Shader* s_currentBoundShader;
			};
		}
	}
}