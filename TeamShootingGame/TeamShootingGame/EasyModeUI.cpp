#include "EasyModeUI.h"
#include "Image.h"

HRESULT EasyModeUI::Init()
{
	size = 96;
	pos = { 200.f, 150.f };
	count = 0;

	img = ImageManager::GetSingleton()->FindImage("Easy_Tile");
	for (int i = 0; i < 18; i++)
	{
		if (i < 5)
		{
			tile[i].pos = { pos.x + i* 150.0f, pos.y };
		}
		else if (i >= 5 && i < 9)
		{
			tile[i].pos = { pos.x + (i - 5) *  150.0f, pos.y + 150.f };
		}
		else if (i >= 9 && i < 13)
		{
			tile[i].pos = { pos.x + (i - 9) *  150.0f, pos.y + 300.f };
		}
		if (i >= 13)
		{
			tile[i].pos = { pos.x + (i - 13) * 150.0f, pos.y + 450.f };
		}
		tile[i].isClear = false;
	}

	for (int i = 0; i < 18/*마지막보스없어서*/; i++)
	{
		tilePos[i] = tile[i].pos;
		TileNum[i] = EnemyName(i);
	}
	return S_OK;
}

void EasyModeUI::Release()
{
}

void EasyModeUI::Update()
{
	count++;
	if (count >= 18)
	{
		count = 0;
	}
}

void EasyModeUI::Render(HDC hdc)
{
	for (int i = 0; i < 18; i++)
	{
		if (img)
		{
			img->FrameRender(hdc, tile[i].pos.x, tile[i].pos.y, i, tile[i].isClear);
		}
	}
}

void EasyModeUI::UpMouseCurser()
{
}

void EasyModeUI::MouseLButtonClick()
{
}

FPOINT EasyModeUI::GetTilePos()
{
	return tilePos[this->count];
}

EnemyName EasyModeUI::GetTileNum()
{
	return TileNum[this->count];
}
