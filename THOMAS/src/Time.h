#pragma once
#include "Common.h"
#include <Windows.h>

/**
*Time calss, holds delta time(DT), FPS and timescale.
*Timescale is for slowmotion or speedup.
*/

namespace thomas
{
	class THOMAS_API Time
	{
	private:

	public:
		static bool Init();

		static void Update();

		static LONG GetDT();

		static float GetFPS();

		static float GetTimescale();

	private:
		static LONG s_oldDT;
		static LONG s_newDT;
		static LONG s_DT;
		static float s_FPS;
		static float s_timescale;
	public:

	};
}