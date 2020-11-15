#pragma once
#include "pch.h"
#include "Singleton.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
private:
	Timer* timer;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetElapsedTime();
};
