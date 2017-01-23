#pragma once
#include "../../Common.h"
#include "Shader.h"
#include <vector>
namespace thomas {
	namespace graphics {
		namespace shader {
			class THOMAS_API ShaderManager {
			private:
			public:
				static bool AddShader(Shader* shader);
				static Shader* GetShader(std::string name);
			private:
				static std::vector<Shader*> s_loadedShaders;

			};
		}
	}
}