#include "PhongMaterial.h"
#include "../../utils/d3d.h"
namespace thomas
{
	namespace graphics
	{
		namespace material
		{
			PhongMaterial::PhongMaterial(std::string name, aiMaterial* material): Material(name, Shader::GetShaderByName("Phong"))
			{
				m_materialProperties.ambientColor = utils::AssimpLoader::GetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE);

				m_materialPropertiesBuffer = utils::D3d::CreateBufferFromStruct(m_materialProperties, D3D11_BIND_CONSTANT_BUFFER);
			}
		}
	}
}
