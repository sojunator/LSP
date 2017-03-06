#pragma once

#include <Thomas.h>

class IslandObject : public GameObject
{
public:
	IslandObject() : GameObject("IslandObject")
	{
	}
	~IslandObject();

private:

};

IslandObject::~IslandObject()
{
}
