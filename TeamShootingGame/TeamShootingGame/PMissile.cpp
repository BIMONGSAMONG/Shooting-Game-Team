#include "PMissile.h"

HRESULT PMissile::Init()
{
	isFire = false;
	size = 10;
	angle = PI / 2;
	pos = { 0, 0 };
	speed = 2.0f;
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
		Rectangle(hdc, pos.x - (size / 2), pos.y - (size * 3), pos.x + (size / 2), pos.y - (size * 2));
	}
}
