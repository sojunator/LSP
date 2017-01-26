#pragma once
#include <Thomas.h>
#include <string>

#include "CameraObject.h"

using namespace thomas;
using namespace object;
class TestObject : public GameObject
{

private:

public:
	TestObject() : GameObject("TestObject") {};


	struct MVPMatrix {
		math::Matrix mvpMatrix;
	};

	bool Start()
	{
		m_mesh = AddComponent<component::MeshComponent>();
		m_mesh->SetMesh("g  Mesh Mesh");

		m_cameraObject = (CameraObject*)Find("CameraObject");

		m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 5));
	//	m_cameraObject->m_transform->LookAt(m_transform);

		m_shader = thomas::graphics::Shader::CreateShader("testShader", "../res/shaders/test.hlsl", thomas::graphics::Shader::InputLayouts::STANDARD);


		m_mvpBuffer = utils::D3d::CreateBufferFromStruct(m_mvpMatrix, D3D11_BIND_CONSTANT_BUFFER);

		return true;
	}


	void Update()
	{
		component::Camera* cam = m_cameraObject->GetComponent<component::Camera>();

		if (Input::GetKey(Input::Keys::A))
		{
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Right()*0.01);
		}
		if (Input::GetKey(Input::Keys::D))
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Right()*0.01);
		}
		if (Input::GetKey(Input::Keys::W))
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Up()*0.01);
		}
		if (Input::GetKey(Input::Keys::S))
		{
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Up()*0.01);
		}

		m_cameraObject->m_transform->LookAt(m_transform);


		cam->SetAspectRatio(16 / 9);
		m_mvpMatrix.mvpMatrix = m_transform->GetWorldMatrix() * m_cameraObject->GetCameraMatrix();

		m_mvpMatrix.mvpMatrix = m_mvpMatrix.mvpMatrix.Transpose();

		utils::D3d::FillBuffer(m_mvpBuffer, m_mvpMatrix);

		m_shader->Bind();

		m_shader->BindBuffer(m_mvpBuffer, graphics::Shader::ResourceType::MVP_MATRIX);

		m_shader->SetMeshData(m_mesh->GetMeshData());
		m_shader->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ThomasCore::GetDeviceContext()->DrawIndexed(m_mesh->GetIndexCount(), 0, 0);
		m_shader->Unbind();
		//LOG("update");
	}

private:
	MVPMatrix m_mvpMatrix;
	CameraObject* m_cameraObject;

	component::MeshComponent* m_mesh;
	thomas::graphics::Shader* m_shader;

	ID3D11Buffer* m_mvpBuffer;

};