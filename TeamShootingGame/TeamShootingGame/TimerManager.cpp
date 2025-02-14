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
	//if (timer)
	//{
	//	wsprintf(szText, "FPS : %d", timer->GetFps());
	//	TextOut(hdc, WINSIZE_X - 100, 40, szText, strlen(szText));
	//}
	
}

float TimerManager::GetElapsedTime()
{
	return timer->GetElapsedTime();
}