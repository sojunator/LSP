#pragma once
#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;
class TestPointLight : public GameObject
{
private:

public:
	TestPointLight() : GameObject("TestPointLight")
	{
		m_pointLight = AddComponent<component::PointLight>();
		
	}

	bool Start()
	{
		m_transform->SetPosition(thomas::math::Vector3(0, 5, -18));
		m_pointLight->SetPower(5);
		m_pointLight->SetConstantAttenuation(2);
		m_pointLight->SetLinearAttenuation(0.05);
		return true;
	}
	void Update()
	{
		if (Input::GetKey(Input::Keys::NumPad4))
		{
			m_transform->Translate(thomas::math::Vector3(0,0,0.1));
		}
		if (Input::GetKey(Input::Keys::NumPad6))
		{
			m_transform->Translate(thomas::math::Vector3(0, 0, -0.1));
		}
	
		
	}
private:
	component::PointLight* m_pointLight;

	
};