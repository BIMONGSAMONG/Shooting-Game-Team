#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
	timer = new Timer();
	timer->Init();

	return S_OK;
}

void TimerManager::Release()
{
	delete timer;
}

void TimerManager::Update()
{
	if (timer)
		timer->Tick();
}

void TimerManager::Render(HDC hdc)
{
	
}

float TimerManager::GetElapsedTime()
{
	return timer->GetElapsedTime();
}