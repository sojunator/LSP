#pragma once
#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;
class TestCube : public GameObject
{

private:

public:
	float forwardSpeed = 0;
	TestCube() : GameObject("testCube")
	{

	}

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("box");
		m_transform->SetScale(1);
		spawned = false;
	}

	void Update()
	{
		if (!m_transform->GetParent())
		{
			if (Input::GetKey(Input::Keys::Left))
			{
				m_transform->RotateByAxis(math::Vector3(0, 1, 0),math::DegreesToradians(-1000*Time::GetDeltaTime()));
			}
			if (Input::GetKey(Input::Keys::Right))
			{
				m_transform->RotateByAxis(math::Vector3(0,1,0), math::DegreesToradians(1000*Time::GetDeltaTime()));
			}
		}
	
		if (Input::GetKeyDown(Input::Keys::Space) && !spawned)
		{
			spawned = true;
			Instantiate<TestCube>(math::Vector3(5, 0, 0), math::Quaternion::Identity, m_transform, m_scene);
			Instantiate<TestCube>(math::Vector3(-5, 0, 0), math::Quaternion::Identity, m_transform, m_scene);
		}
		if (Input::GetKeyDown(Input::Keys::K) && !spawned && m_transform->GetParent())
		{
			
			LOG(m_transform->GetPosition().x);
			Instantiate<TestCube>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
		}

	}

private:
	bool spawned;
	component::RenderComponent* m_renderer;

};