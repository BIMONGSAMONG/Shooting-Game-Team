#include "TitleScene.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	startScene = ImageManager::GetSingleton()->FindImage("시작화면");
	background = ImageManager::GetSingleton()->FindImage("Z키를 누르세요");
	goMain = false;
	isStart = true;
	startTimer = 0;
	return S_OK;
}

void TitleScene::Release()
{

}

void TitleScene::Update()
{
	if (isStart == true)
	{
		StartSceneTimer();
	}
	if (isStart == false)
	{
		PressZKey();
	}
}

void TitleScene::Render(HDC hdc)
{
	if (background) background->Render(hdc, 0, 0);
	if (isStart == true)
	{
		if (startScene) startScene->Render(hdc, 0, 0);
	}
}

void TitleScene::PressZKey()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(KEY_Z))
	{
		goMain = true;
	}
}

void TitleScene::StartSceneTimer()
{
	startTimer += TimerManager::GetSingleton()->GetElapsedTime();
	if (startTimer >= 2.0f)
	{
		isStart = false;
		startTimer = 2.1f;
	}
}