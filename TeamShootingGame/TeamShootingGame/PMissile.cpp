#include "PMissile.h"
#include "Image.h"

HRESULT PMissile::Init()
{
	isFire = false;
	size = 10;
	angle = PI / 2;
	pos = { 0, 0 };
	speed = 3.2f;

	img[0] = ImageManager::GetSingleton()->FindImage("Player_Bullet");
	img[1] = ImageManager::GetSingleton()->FindImage("Player_Bullet_Black");

	return S_OK;
}

void PMissile::Release()
{
}

void PMissile::Update()
{
	if (isFire == true)
	{
		pos.x += cosf(angle) * speed;
		pos.y -= sinf(angle) * speed;
		if (pos.y < 0)
		{
			isFire = false;
		}
	}
}

void PMissile::Render(HDC hdc)
{
	if (isFire)
	{
		if (img)
		{
			if (boss != EnemyName::Despair)
			{
				img[0]->Render(hdc, pos.x, pos.y);
			}
			if (boss == EnemyName::Despair)
			{
				img[1]->Render(hdc, pos.x, pos.y);
			}
		}
	}
}
