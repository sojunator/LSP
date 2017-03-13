#pragma once
#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;
class TestDirectionalLight : public GameObject
{
private:

public:
	TestDirectionalLight() : GameObject("TestDirectionalLight")
	{

	}

	void Start()
	{
		m_dirLight = AddComponent<component::DirectionalLight>();
		
		m_lightColor = math::Vector4(1.0f, 1.0f, 0.6f, 1);
		m_dirLight->SetLightColor(m_lightColor);
		m_rot = 0;
		m_transform->SetPosition(math::Vector3(50, 50, 50));
		m_transform->LookAt(m_transform);

	}
	void Update()
	{
		m_dirLight->SetLightColor(m_lightColor);
		float rotFactor = 3 * ThomasTime::GetDeltaTime();
		if (Input::GetKey(Input::Keys::NumPad4))
		{
			m_rot -= rotFactor;
		}
		if (Input::GetKey(Input::Keys::NumPad6))
		{
			m_rot += rotFactor;
		}
		m_transform->SetRotation(m_rot, 0, 0);
		
	}
private:
	component::DirectionalLight* m_dirLight;
	math::Color m_lightColor;
	float m_rot;
};