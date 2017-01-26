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
	TestObject() : GameObject("TestObject") 
	{
		m_renderer = AddComponent<component::RenderComponent>();

	}

	bool Start()
	{
		

		m_renderer->SetModel("testModel");
		
		m_cameraObject = (CameraObject*)Find("CameraObject");

		//m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 50));
		m_transform->SetPosition(math::Vector3(0, 0, -5));
		m_cameraObject->GetComponent<component::Camera>()->SetAspectRatio(16 / 9);

		worldmatrixbuffer = utils::D3d::CreateBufferFromStruct(m_matrix, D3D11_BIND_CONSTANT_BUFFER);


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

		m_matrix.matrix = m_transform->GetWorldMatrix() * cam->GetViewProjMatrix();
		m_matrix.matrix = m_matrix.matrix.Transpose();

		utils::D3d::FillBuffer(worldmatrixbuffer, m_matrix);


		thomas::graphics::Shader::GetCurrentBoundShader()->BindBuffer(worldmatrixbuffer, thomas::graphics::Shader::ResourceType::MVP_MATRIX);


		thomas::graphics::Shader::GetCurrentBoundShader()->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		for (int i = 0; i < m_renderer->GetModel()->GetMeshes().size(); i++)
		{
			m_renderer->GetModel()->GetMeshes()[i]->GetMaterial()->Bind();
			m_renderer->GetModel()->GetMeshes()[i]->Bind();
			m_renderer->GetModel()->GetMeshes()[i]->Draw();
		}


	}

private:


	struct WorldMatrix {
		math::Matrix matrix;
	};
	ID3D11Buffer* worldmatrixbuffer;
	WorldMatrix m_matrix;
	CameraObject* m_cameraObject;
	component::RenderComponent* m_renderer;

};