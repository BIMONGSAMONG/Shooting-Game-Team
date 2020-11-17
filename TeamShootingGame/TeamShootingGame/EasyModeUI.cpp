#include "EasyModeUI.h"
#include "Image.h"

HRESULT EasyModeUI::Init()
{
	size = 96;
	pos = { 100.f, 50.f };
	count = 0;


	for (int i = EnemyName::Tile_Start + 1; i < EnemyName::TILE_END_NUM; i++)
	{
		if ((i - 20) < 5)
		{
			tile[i].pos = { pos.x + (i - 20) * 175.0f, pos.y };
		}
		else if ((i - 20) >= 5 && (i - 20) < 9)
		{
			tile[i].pos = { pos.x + (i - 25) *  175.0f, pos.y + 150.f };
		}
		else if ((i - 20) >= 9 && (i - 20) < 13)
		{
			tile[i].pos = { pos.x + (i - 29) *  175.0f, pos.y + 300.f };
		}
		if ((i - 20) >= 13)
		{
			tile[i].pos = { pos.x + (i - 33) * 175.0f, pos.y + 450.f };
		}
		tile[i].isClear = false;
		tile[i].img = ImageManager::GetSingleton()->FindImage(i);
	}

	for (int i = EnemyName::Tile_Start + 1; i < EnemyName::TILE_END_NUM-1/*마지막보스없어서*/; i++)
	{
		tilePos[i-20] = tile[i].pos;
		TileNum[i-20] = EnemyName(i - 20);
	}
	return S_OK;
}

void EasyModeUI::Release()
{
}

void EasyModeUI::Update()
{
	count++;
	if (count == 17)
	{
		count = 0;
	}
}

void EasyModeUI::Render(HDC hdc)
{
	for (int i = EnemyName::Tile_Start + 1; i < EnemyName::TILE_END_NUM; i++)
	{
		if (tile[i].img)
		{
			tile[i].img->Render(hdc, tile[i].pos.x, tile[i].pos.y);
			//Rectangle(hdc, tile[i].pos.x , tile[i].pos.y , tile[i].pos.x + size , tile[i].pos.y + size);
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

//void EasyModeUI::ImageRender(HDC hdc, int name)
//{
//	if (tile[name].isClear == true)
//	{
//		
//	}
//}
