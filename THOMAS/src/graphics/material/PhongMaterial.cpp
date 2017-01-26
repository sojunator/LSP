#include "PhongMaterial.h"
#include "../../utils/d3d.h"
namespace thomas
{
	namespace graphics
	{
		namespace material
		{
			PhongMaterial::PhongMaterial(std::string dir, std::string name, aiMaterial* material): Material(dir, name, Shader::GetShaderByName("Phong"), material)
			{
				m_materialProperties.ambientColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT);

				m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);

				
			}
		}
	}
}
