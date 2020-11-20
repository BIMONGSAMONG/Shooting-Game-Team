#include "Player.h"
#include "PMissileManager.h"
#include "Image.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	size = 4;
	isBoss = false;
	die = false;
	missileMgr = new PMissileManager;
	missileMgr->Init();

	img[0] = ImageManager::GetSingleton()->FindImage("Player_White");
	img[1] = ImageManager::GetSingleton()->FindImage("Player_Black");
	timerDelay = 0.0f;
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
	
	Fire();
	
	if (missileMgr)
	{
		missileMgr->Update();
	}
	if (die)
	{
		pos = { WINSIZE_X / 2, WINSIZE_Y - 100 };
	}
}

void Player::Render(HDC hdc)
{
	if (img)
	{
		if (die == false)
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
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= timerDelay)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(KEY_Z))
		{
			if (missileMgr)
			{
				if (die == false)
				{
					missileMgr->Fire(pos);
					timer = 0;
					timerDelay = 0.4;
				}
			}
		}
	}
}
