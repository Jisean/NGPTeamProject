#pragma once
#include "stdafx.h"

class Timer
{
private:
	LARGE_INTEGER			m_FrameTime;
	LARGE_INTEGER			m_FixTime;
	LARGE_INTEGER			m_LastTime;
	LARGE_INTEGER			m_CpuTick;
private:
	float m_fTime;
public:
	float GetTime(void);
	void  InitTime(void);
	void  SetTime(void);

public:
	Timer(void);
	~Timer(void);
};