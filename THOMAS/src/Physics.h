#pragma once
#include "Common.h"
#include "../include/btBulletDynamicsCommon.h"
namespace thomas
{
	class THOMAS_API Physics
	{
	private:
	public:
		static btDiscreteDynamicsWorld* s_world;
		static bool Init();
		static void Update();
		static void Destroy();
	private:
		
	};
}