#include "PhongMaterial.h"
namespace thomas
{
	namespace graphics
	{
		namespace material
		{
			PhongMaterial::PhongMaterial(std::string name, aiMaterial* material): Material(name, Shader::GetShaderByName("Phong"))
			{
				m_materialProperties.ambientColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT);
			}
		}
	}
}
