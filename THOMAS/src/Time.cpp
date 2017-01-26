#include "Time.h"

bool thomas::Time::Init()
{
	s_oldDT = GetTickCount64();		///Returns milliseconds since system was started
	s_newDT = GetTickCount64();
	s_DT = 0;
	s_timescale = 1;
	return true;
}

void thomas::Time::Update()
{
	s_oldDT = s_newDT;
	s_newDT = GetTickCount64();
	s_DT = s_newDT - s_oldDT;

	s_FPS = 1 / s_DT;
}

LONG thomas::Time::GetDT()
{
	return s_DT;
}

float thomas::Time::GetFPS()
{
	return s_FPS;
}

float thomas::Time::GetTimescale()
{
	return s_timescale;
}
