#pragma once
#include <Thomas.h>
#include "ShipStats.h"

using namespace thomas;
using namespace object;
class PauseObjectMenuObject : public GameObject
{

private:

public:
	PauseObjectMenuObject() : GameObject("PauseObjectMenuObject")
	{

	}
	~PauseObjectMenuObject()
	{
	}

	void Start()
	{
		isPaused = false;
	}
	void CheckState()
	{
		if (Input::GetKeyDown(Input::Keys::Space))
		{
			if (isPaused)
			{
				ThomasTime::SetTimescale(1.0f);
				isPaused = false;
			}
			else
			{
				ThomasTime::SetTimescale(0.0f);
				isPaused = true;
			}
		}


	}
	void Update()
	{
		CheckState();
		//draw that meny

	};



private:
	bool isPaused;
};
