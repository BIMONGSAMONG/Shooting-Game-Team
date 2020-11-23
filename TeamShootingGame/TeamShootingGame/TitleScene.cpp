#include "TitleScene.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	background = ImageManager::GetSingleton()->FindImage("Z키를 누르세요");
	goMain = false;
	return S_OK;
}

void TitleScene::Release()
{

}

void TitleScene::Update()
{
	PressZKey();
}

void TitleScene::Render(HDC hdc)
{
	if (background) background->Render(hdc, 0, 0);
}

void TitleScene::PressZKey()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(KEY_Z))
	{
		goMain = true;
	}
}