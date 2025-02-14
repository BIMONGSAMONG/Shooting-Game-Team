#pragma once
#include "pch.h"

class Timer
{
private:
	bool isHardware;	// 고성능 타이머를 쓸 수 있는지 여부
	float timeScale;	// 경과 진동수를 초당 진동수로 나눠서 진동수를 시간단위로 변환
	float timeElapsed;	// 마지막 시간과 현재 시간의 경과량
	__int64 currTime;	// 현재 시간 (고성능 타이머 값)
	__int64 lastTime;	// 이전 시간 (고성능 타이머 값)
	__int64 periodFrequency;	// 고성능 타이머의 주파수 (초당 진동수), 지원하지 않으면 0 반환

	float fpsTimeElapsed;			// 프레임 경과 시간 (1초확인)
	unsigned long fpsFrameCount;	// 초당 프레임 수
	unsigned long fps;

public:
	HRESULT Init();
	void Tick();
	unsigned long GetFps() { return this->fps; }
	float GetElapsedTime() { return timeElapsed; }
};
