#include "Player.h"
#include "PMissileManager.h"
#include "Image.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	size = 4;
	isBoss = false;

	missileMgr = new PMissileManager;
	missileMgr->Init();

	img[0] = ImageManager::GetSingleton()->FindImage("Player_White");
	img[1] = ImageManager::GetSingleton()->FindImage("Player_Black");
	
	return S_OK;
}

void Player::Release()
{
	missileMgr->Release();
	delete missileMgr;
}

void Player::Update()
{
	Move();
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= 0.3f)
	{
		Fire();
		timer = 0.0f;
	}
	
	if (missileMgr)
	{
		missileMgr->Update();
	}
}

void Player::Render(HDC hdc)
{
	if (img)
	{
		if (isBoss == false)
		{
			img[0]->Render(hdc, pos.x, pos.y);
		}
		else if (isBoss == true)
		{
			img[1]->Render(hdc, pos.x, pos.y);
		}
	}

	if (missileMgr)
	{
		missileMgr->Render(hdc);
	}
}

void Player::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_LEFT))
	{
		pos.x -= 1;
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_RIGHT))
	{
		pos.x += 1;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_UP))
	{
		pos.y -= 1;
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_DOWN))
	{
		pos.y += 1;
	}
}

void Player::Fire()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_Z))
	{
		if (missileMgr)
		{
			missileMgr->Fire(pos);
		}
	}
}
