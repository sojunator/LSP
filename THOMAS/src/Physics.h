#pragma once
#include "Common.h"
#include "../include/btBulletDynamicsCommon.h"
#include "graphics\BulletDebugDraw.h"
#include "object\component\Camera.h"
namespace thomas
{
	class THOMAS_API Physics
	{
	private:
	public:
		static btDiscreteDynamicsWorld* s_world;
		static bool Init();
		static void Update();
		static void DrawDebug(object::component::Camera* camera);
		static void Destroy();
		static graphics::BulletDebugDraw* getDebugDraw();
	private:
		static graphics::BulletDebugDraw* s_debugDraw;
		static float s_accumulator;
	};
}