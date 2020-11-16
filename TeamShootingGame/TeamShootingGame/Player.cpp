#include "Player.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	size = 20;
	return E_NOTIMPL;
}

void Player::Release()
{
}

void Player::Update()
{
}

void Player::Render(HDC hdc)
{
	Rectangle(hdc, pos.x - (size / 2) + 5, pos.y - size, pos.x + (size / 2) - 5, pos.y + size);
}

void Player::Move()
{
}

void Player::Fire()
{
}
