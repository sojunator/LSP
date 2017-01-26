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

		static void Update();		///Updates delta time and FPS

		static float GetDT();		///Delta time

		static int GetFPS();

		static void SetTimescale(float timescale);		///The smaller the timescale the slower the time
		static float GetTimescale();

	private:
		static LONGLONG s_oldDT;
		static LONGLONG s_newDT;
		static float s_DT;
		static int s_FPS;
		static float s_timescale;
	public:

	};
}