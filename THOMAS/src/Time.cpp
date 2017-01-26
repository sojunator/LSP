#include "Time.h"

namespace thomas
{
	LONGLONG Time::s_oldDT;
	LONGLONG Time::s_newDT;
	float Time::s_DT;
	int Time::s_FPS;
	float Time::s_timescale;

	bool Time::Init()
	{
		s_oldDT = 0;
		s_newDT = GetTickCount64();		///Returns milliseconds since system was started
		s_DT = 0;
		s_FPS = 0;
		s_timescale = 1;
		return true;
	}

	void Time::Update()
	{
		s_oldDT = s_newDT;
		s_newDT = GetTickCount64();
		s_DT = (s_newDT - s_oldDT)/1000.0;
		if(s_DT > 0.0)
			s_FPS = 1.0 / s_DT;
	}

	float Time::GetDT()
	{
		return s_DT * s_timescale;
	}

	int Time::GetFPS()
	{
		return s_FPS;
	}

	void Time::SetTimescale(float timescale)
	{
		s_timescale = timescale;
	}

	float Time::GetTimescale()
	{
		return s_timescale;
	}
}