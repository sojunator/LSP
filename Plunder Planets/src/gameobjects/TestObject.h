#pragma once
#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;
class TestObject : public GameObject
{

private:

public:
	TestObject() : GameObject("TestObject") {};

	bool Start()
	{
		m_mesh = AddComponent<component::MeshComponent>();
		m_mesh->SetMesh("1");
		m_shader = thomas::graphics::Shader::CreateShader("testShader", "../res/shaders/test.hlsl", thomas::graphics::Shader::InputLayouts::STANDARD);
		m_transform->SetPosition(math::Vector3(0, 0, 0));

		return true;
	}


	void Update()
	{
		m_shader->Bind();
		m_shader->SetMeshData(m_mesh->GetMeshData());
		m_shader->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ThomasCore::GetDeviceContext()->DrawIndexed(m_mesh->GetIndexCount(), 0, 0);
		m_shader->Unbind();
		//LOG("update");
	}

private:
	component::MeshComponent* m_mesh;
	thomas::graphics::Shader* m_shader;

};