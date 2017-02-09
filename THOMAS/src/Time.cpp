#include "Time.h"
#include <Windows.h>
namespace thomas
{
	double Time::s_initTime;
	double Time::s_startTime;
	double Time::s_timeFreq;
	double Time::s_DeltaTime;
	float Time::s_FPS;
	float Time::s_FrameTime;
	float Time::s_timescale;

	bool Time::Init()
	{
		LARGE_INTEGER freq;
	//	timeBeginPeriod(1);
		if (!QueryPerformanceFrequency(&freq))LOG("QueryPerformanceFrequency failed!!!!");
		s_timeFreq = double(freq.QuadPart);

		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		s_initTime = double(currentTime.QuadPart);
		s_startTime = double(currentTime.QuadPart);
		s_FPS = 0;
		s_timescale = 1;
		return true;
	}

	void Time::Update()
	{

		s_DeltaTime = GetElapsedTime();	
		s_FPS = 1.0 / s_DeltaTime;
		s_FrameTime = 1000.0 / s_FPS;
	}

	float Time::GetDeltaTime()
	{
		return s_DeltaTime * s_timescale;
	}

	double Time::GetInitTime()
	{
		return s_initTime;
	}

	int Time::GetFPS()
	{
		return s_FPS;
	}

	float Time::GetFrameTime()
	{
		return 1000.0 / s_FPS;
	}

	void Time::SetTimescale(float timescale)
	{
		s_timescale = timescale;
	}

	float Time::GetTimescale()
	{
		return s_timescale;
	}


	double Time::GetElapsedTime()
	{

		LARGE_INTEGER newTime;
		QueryPerformanceCounter(&newTime);
		double elapsed = double(newTime.QuadPart - s_startTime)/ s_timeFreq;
		s_startTime = newTime.QuadPart;
		return elapsed;
	}

}