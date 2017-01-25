#include "TestObject.h"

using namespace thomas;
using namespace object;
bool TestObject::Start()
{
	utils::Model model = thomas::utils::AssimpLoader::LoadModel("../THOMAS/objects/bb8.obj");
	m_shader = thomas::graphics::Shader::CreateShader("testShader", "../res/shaders/test.hlsl", thomas::graphics::Shader::InputLayouts::STANDARD);
	m_mesh = model.meshes[0];
	
	m_transform->SetPosition(math::Vector3(0, 0, 0));

	return true;
}

void TestObject::Update()
{

	m_shader->Bind();
	m_shader->SetMeshData(m_mesh->GetData());
	m_shader->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ThomasCore::GetDeviceContext()->DrawIndexed(m_mesh->GetData()->indices.size(), 0, 0);
	//m_shader->Unbind();
	//LOG("update");
}
