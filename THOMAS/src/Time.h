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
		static double GetElapsedTime();
	public:
		static bool Init();

		static void Update();		///Updates delta time and FPS

		static float GetDeltaTime();		///Delta time

		static int GetFPS();

		static void SetTimescale(float timescale);		///The smaller the timescale the slower the time
		static float GetTimescale();

		

	private:
		static double s_startTime;
		static double s_timeFreq;
		static double s_DeltaTime;
		static int s_FPS;
		static float s_timescale;
	public:

	};
}