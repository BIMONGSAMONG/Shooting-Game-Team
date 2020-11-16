#include "Player.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	size = 10;
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
}

void Player::Move()
{
}

void Player::Fire()
{
}
