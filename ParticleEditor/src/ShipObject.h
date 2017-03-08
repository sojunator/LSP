#pragma once

#include <Thomas.h>

using namespace thomas;
using namespace object;
class ShipObject : public GameObject
{

private:

public:
	ShipObject() : GameObject("ShipObject")
	{

	};

	void Start()
	{
		m_transform->SetPosition(0, 20, 0);
		m_ship = AddComponent<component::RenderComponent>();
		m_ship->SetModel("ship");
	};
	void Update()
	{
		if (Input::GetKey(Input::Keys::Left))
		{
			m_transform->RotateByAxis(math::Vector3::Up, -10 * ThomasTime::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::Right))
		{
			m_transform->RotateByAxis(math::Vector3::Up, 10 * ThomasTime::GetDeltaTime());
		}
	}


private:
	component::RenderComponent* m_ship;
};