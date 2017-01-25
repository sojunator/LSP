#include "TestObject.h"

using namespace thomas;
using namespace object;
bool TestObject::Start()
{
	utils::Model model = thomas::utils::AssimpLoader::LoadModel("../res/models/sphere1.obj");
	m_shader = thomas::graphics::Shader::CreateShader("testShader", "../res/shaders/test.hlsl", thomas::graphics::Shader::InputLayouts::STANDARD);
	m_mesh = model.meshes[0];
	
	m_transform->SetPosition(math::Vector3(0, 0, 0));
	m_wmData.worldMatrix = m_transform->GetWorldMatrix();
	m_testCBuffer = thomas::utils::D3d::CreateBufferFromStruct(m_wmData, D3D11_BIND_CONSTANT_BUFFER);

	return true;
}

void TestObject::Update()
{
	m_wmData.worldMatrix = m_transform->GetWorldMatrix();
	thomas::utils::D3d::FillBuffer(m_testCBuffer, m_wmData);
	
	m_shader->Bind();
	m_shader->BindBuffer(m_testCBuffer, thomas::graphics::Shader::ResourceType::MVP_MATRIX);
	m_shader->SetMeshData(m_mesh->GetData());
	m_shader->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ThomasCore::GetDeviceContext()->DrawIndexed(m_mesh->GetData()->indices.size(), 0, 0);
	//m_shader->Unbind();
	//LOG("update");
}
