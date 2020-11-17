#include "EasyModeUI.h"
#include "Image.h"

HRESULT EasyModeUI::Init()
{
	size = 96;
	pos = { 150.0f, 100.f };
	for (int i = 0; i < EnemyName::NUM; i++)
	{
		tile[i].isClear = false;
		tile[i].img = ImageManager::GetSingleton()->FindImage(i);
		if (i < 5)
		{
			tile[i].pos = { pos.x + i * 150.0f, pos.y };
		}
		else if (i >= 5 && i < 9)
		{
			tile[i].pos = { pos.x + (i - 5) * 150.0f, pos.y + 150.f };
		}
		else if (i >= 9 && i < 13)
		{
			tile[i].pos = { pos.x + (i - 9) * 150.0f, pos.y + 300.f };
		}
		if (i >= 13)
		{
			tile[i].pos = { pos.x + (i - 13) * 150.0f, pos.y + 450.f };
		}
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
			if (tile[i].img)
			{
				tile[i].img->Render(hdc, tile[i].pos.x, tile[i].pos.y);
			}
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
//		
//	}
//}
