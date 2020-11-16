#include "EasyModeUI.h"
#include "Image.h"

HRESULT EasyModeUI::Init()
{
	size = 96;
	for (int i = 0; i < 18; i++)
	{
		if (i / 5 == 2 || i / 5 == 3)
		{
			tile[i].pos = { 200.0f + (i % 4) * 100.0f, 50.0f + (i / 5) * 100.0f };
		}
		else
		{
			tile[i].pos = { 200.0f + (i % 5) * 100.0f, 50.0f + (i / 5) * 100.0f };
		}
		tile[i].isClear = false;
	}
	return S_OK;
}

void EasyModeUI::Release()
{
}

void EasyModeUI::Update()
{
}

void EasyModeUI::Render(HDC hdc)
{
	for (int i = 0; i < EnemyName::NUM; i++)
	{
		Rectangle(hdc, tile[i].pos.x - (size / 2), tile[i].pos.y - (size / 2), tile[i].pos.x + (size / 2), tile[i].pos.y) + (size / 2);
	}
}

void EasyModeUI::UpMouseCurser()
{
}

void EasyModeUI::MouseLButtonClick()
{
}

//void EasyModeUI::ImageRender(HDC hdc, int name)
//{
//	if (tile[name].isClear == true)
//	{
//		tile[name].img->
//	}
//}
