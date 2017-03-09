#pragma once

#include <Thomas.h>

using namespace thomas;
using namespace object;
class Plane : public GameObject
{

private:

public:
	Plane() : GameObject("Plane")
	{

	};

	void Start()
	{
		m_plane = AddComponent<component::RenderComponent>();
		m_plane->SetModel("plane");
	};
	void Update()
	{
	}


private:
	component::RenderComponent* m_plane;
};