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
		m_dirLight = AddComponent<component::DirectionalLight>();
		m_transform->SetRotation(0.936016f, -0.343206f, 0.0780013f);
		m_dirLight->SetLightColor(math::Vector4(1.0f, 1.0f, 0.6f, 1));
	}

	bool Start()
	{
		m_rot = 0;
		return true;
	}
	void Update()
	{
		float rotFactor = 3 * Time::GetDeltaTime();
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
	float m_rot;
};