#include "EMissileManager.h"
#include "EMissile.h"

HRESULT EMissileManager::Init()
{
	isShoot = true;
	isShake = false;
	enemyMissileCount = 400;
	vecMissiles.reserve(enemyMissileCount);
	for (int i = 0; i < enemyMissileCount; i++)
	{
		vecMissiles.push_back(new EMissile());
		vecMissiles[i]->Init();
	}

	angle = 0.0f;
	addAngle1 = PI / 3;
	addAngle2 = ((2 * PI) / 9);

	fireTime = 0.0f;
	count = 1;
	isPattern = false;
	bulletCount = 0;
	randomPos = { 0, 0 };
	vertexPos1 = { 0, 0 };
	vertexPos2 = { WINSIZE_X, 0 };

	return S_OK;
}

void EMissileManager::Release()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Release();
		delete (*itMissiles);
	}
	vecMissiles.clear();
}

void EMissileManager::Update(EnemyName name, FPOINT pos, float destAngle, float fireDelay, Mode mode)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Update();
	}

	fireTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (fireTime >= fireDelay)
	{
		if (isShoot)
		{
			Fire(name, pos, destAngle, mode);
		}
		count++;
		fireTime = 0.0f;
		randomPos.x = rand() % WINSIZE_X + 1;
		if (isShoot == false)
		{
			isShake = false;
		}
	}
}

void EMissileManager::Render(HDC hdc, EnemyName name, Mode mode)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Render(hdc, name, mode);
	}
}

void EMissileManager::Fire(EnemyName name, FPOINT pos, float destAngle, Mode mode)
{
	switch (name)
	{
	case Irritation:
		if (mode == Mode::Easy)
		{
			for (int i = 0 + bulletCount; i < 1 + bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetAngle(destAngle);
					vecMissiles[i]->SetSpeed(1300);
					vecMissiles[i]->SetIsFire(true);
				}
			}
			bulletCount++;
			if (bulletCount >= 180)
			{
				bulletCount = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
		}
		break;
	case Pressure:
		if (mode == Mode::Easy)
		{
			angle += addAngle1 - (PI / 4);
			for (int i = 0 + bulletCount; i < 6 + bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetAngle(angle + addAngle1 * i + (PI / 4));
					vecMissiles[i]->SetSpeed(1000.0f);
					vecMissiles[i]->SetIsFire(true);
				}
			}
			bulletCount+=6;
			if (bulletCount >= 180)
			{
				bulletCount = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			angle += addAngle2 - (PI / 4);
			for (int i = 0 + bulletCount; i < 9 + bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetAngle(angle + addAngle2 * i + (PI / 4));
					vecMissiles[i]->SetSpeed(1000.0f);
					vecMissiles[i]->SetIsFire(true);
				}
			}
			bulletCount += 9;
			if (bulletCount >= 180)
			{
				bulletCount = 0;
			}
		}
		break;
	case Loneliness:
		if (mode == Mode::Easy)
		{
			for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			{
				if (count <= 3) // 3발까지는 쏘고
				{
					if ((*itMissiles)->GetIsFire() == false)
					{
						(*itMissiles)->SetPos(pos);
						(*itMissiles)->SetAngle(destAngle);
						(*itMissiles)->SetSpeed(1300);
						(*itMissiles)->SetIsFire(true);
						break;
					}
				}
			}
			 //break로 나오면 ++
			if (count == 10) // 6가 될때까지는 쏘지말아라
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			{
				if (count <= 7) // 7발까지는 쏘고
				{
					if ((*itMissiles)->GetIsFire() == false)
					{
						(*itMissiles)->SetPos(pos);
						(*itMissiles)->SetAngle(destAngle);
						(*itMissiles)->SetSpeed(1580);
						(*itMissiles)->SetIsFire(true);
						break;
					}
				}
			}
			if (count == 15) // 10 될때까지는 쏘지말아라
			{
				count = 0;
			}
		}
		break;
	case Distress:
		if (mode == Mode::Easy)
		{
			if(count == 1)
			for (int i = 0 + bulletCount; i < 3 + bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetAngle(destAngle + ((i - 1 - bulletCount) / 6.0f));
					vecMissiles[i]->SetSpeed(1000.0f);
					vecMissiles[i]->SetIsFire(true);
				}
			}
			bulletCount += 3;
			if (bulletCount >= 180)
			{
				bulletCount = 0;
			}
			if (count >= 5)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			if (count == 1)
			{
				for (int i = 0 + bulletCount; i < 3 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetAngle(destAngle + ((i - 1 - bulletCount) / 6.0f));
						vecMissiles[i]->SetSpeed(1200.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			else if (count == 2)
			{
				for (int i = 3 + bulletCount; i < 7 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetAngle(destAngle + ((i - 5 - bulletCount) / 6.0f) + 0.08f);
						vecMissiles[i]->SetSpeed(1200.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			bulletCount += 7;
			if (bulletCount >= 182)
			{
				bulletCount = 0;
			}
			if (count >= 7)
			{
				count = 0;
			}
		}
		break;
	case Fear:
		if (mode == Mode::Easy)
		{
			for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			{
				if ((*itMissiles)->GetIsFire() == false)
				{
					(*itMissiles)->SetPos(randomPos);
					(*itMissiles)->SetAngle(-PI / 2.0f);
					(*itMissiles)->SetSpeed(2100);
					(*itMissiles)->SetIsFire(true);
					break;
				}
			}
		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Hatred:
		if (mode == Mode::Easy)
		{
			if (count == 1)
			{
				for (int i = 0 + bulletCount; i < 9 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i  <= 2 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 4 - bulletCount) / 40.0f) - 0.25f);
						}
						else if (i > 2 + bulletCount && i < 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 4 - bulletCount) / 40.0f));
						}
						else if (i >= 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 4 - bulletCount) / 40.0f) + 0.25f);
						}
						vecMissiles[i]->SetSpeed(1300.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			if (count == 3)
			{
				for (int i = 9 + bulletCount; i < 21 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i <= 11 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) - 0.3f);
						}
						else if (i > 11 + bulletCount && i < 15 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) - 0.1f);
						}
						else if (i >= 15 + bulletCount && i < 18 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) + 0.1f);
						}
						else if (i >= 18 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) + 0.3f);
						}
						vecMissiles[i]->SetSpeed(1300.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			bulletCount += 21;
			if (bulletCount >= 189)
			{
				bulletCount = 0;
			}
			if (count >= 8)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			if (count == 1)
			{
				for (int i = 0 + bulletCount; i < 9 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i <= 2 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 4 - bulletCount) / 40.0f) - 0.25f);		// -4, -3, -2
						}
						else if (i > 2 + bulletCount && i < 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 4 - bulletCount) / 40.0f));				// -1, 0, 1
						}
						else if (i >= 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 4 - bulletCount) / 40.0f) + 0.25f);		// 2, 3, 4
						}
						vecMissiles[i]->SetSpeed(1300.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			if (count == 3)
			{
				for (int i = 9 + bulletCount; i < 21 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i <= 11 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) - 0.3f);		// -6, -5, -4
						}
						else if (i > 11 + bulletCount && i < 15 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) - 0.1f);		// -3, -2, -1
						}
						else if (i >= 15 + bulletCount && i < 18 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) + 0.1f);		// 0, 1, 2
						}
						else if (i >= 18 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 15 - bulletCount) / 40.0f) + 0.3f);		// 3, 4, 5
						}
						vecMissiles[i]->SetSpeed(1300.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			if (count == 5)
			{
				for (int i = 21 + bulletCount; i < 30 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i <= 23 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 25 - bulletCount) / 40.0f) - 0.25f);		// -4, -3, -2
						}
						else if (i > 23 + bulletCount && i < 27 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 25 - bulletCount) / 40.0f));				// -1, 0, 1
						}
						else if (i >= 27 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 25 - bulletCount) / 40.0f) + 0.25f);		// 2, 3, 4
						}
						vecMissiles[i]->SetSpeed(1300.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			if (count == 7)
			{
				for (int i = 30 + bulletCount; i < 42 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i <= 32 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 36 - bulletCount) / 40.0f) - 0.3f);		// -6, -5, -4
						}
						else if (i > 32 + bulletCount && i < 36 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 36 - bulletCount) / 40.0f) - 0.1f);		// -3, -2, -1
						}
						else if (i >= 36 + bulletCount && i < 39 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 36 - bulletCount) / 40.0f) + 0.1f);		// 0, 1, 2
						}
						else if (i >= 39 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 36 - bulletCount) / 40.0f) + 0.3f);		// 3, 4, 5
						}
						vecMissiles[i]->SetSpeed(1300.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			if (count == 9)
			{
				for (int i = 42 + bulletCount; i < 84 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetAngle(angle - (PI / 20) * (i - bulletCount));
						vecMissiles[i]->SetSpeed(1300.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}

			bulletCount += 84;
			if (bulletCount >= 230)
			{
				bulletCount = 0;
			}
			if (count >= 16)
			{
				count = 0;
			}
		}
		break;
	case Guilt:
		if (mode == Mode::Easy)
		{
			if (count == 1)
			{
				angle += addAngle1 + (PI / 4);
				for (int i = 0; i < 6; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle + addAngle1 * i + (PI / 4));
							(*itMissiles)->SetSpeed(900.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(false);
							(*itMissiles)->SetIsRightAngle(true);
							(*itMissiles)->SetRightAddAngle(DegreeToRadian(72), 10.0f);
							break;
						}
					}
				}

			}
			if (count == 2)
			{
				for (int i = 0; i < 6; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle + addAngle1 * i + (PI / 4));
							(*itMissiles)->SetSpeed(1000.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(72), 10.0f);
							break;
						}
					}
				}
			}
			if (count == 6)
			{
				count = 0;
			}
			break;
		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Confusion:
		if (mode == Mode::Easy)
		{
			if (count == 1)
			{
				for (int i = 0 + bulletCount; i < 4 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetAngle(0 + addAngle1 * (i - bulletCount));
						vecMissiles[i]->SetSpeed(1000.0f);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
						vecMissiles[i]->SetDisappears(4.0f);
					}
				}
			}
			bulletCount += 4;
			if (bulletCount >= 292)
			{
				bulletCount = 0;
			}
			if (count >= 6)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			if (count == 1)
			{
				for (int i = 0 + bulletCount; i < 4 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetAngle(0 + addAngle1 * (i - bulletCount));
						vecMissiles[i]->SetSpeed(1000.0f);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
						vecMissiles[i]->SetDisappears(4.0f);
					}
				}
			}
			if (count == 3)
			{
				for (int i = 4 + bulletCount; i < 8 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i == 4 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI / 16);
						}
						if (i == 5 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI - (PI / 16));
						}
						if (i == 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(0 - (PI / 16));
						}
						if (i == 7 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI + (PI / 16));
						}
						vecMissiles[i]->SetSpeed(1000.0f);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
						vecMissiles[i]->SetDisappears(4.0f);
					}
				}
			}
			bulletCount += 8;
			if (bulletCount >= 288)
			{
				bulletCount = 0;
			}
			if (count >= 8)
			{
				count = 0;
			}
		}
		break;
	case Emptiness:
		if (mode == Mode::Easy)
		{
			if (count == 1)
			{
				angle = DegreeToRadian(36);
				for (int i = 0; i < 10; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
			}
			if (count == 3)
			{
				for (int i = 0; i < 10; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle((-PI / 2.0f) + angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
			}
			if (count == 19)
			{
				angle = DegreeToRadian(36);
				for (int i = 0; i < 10; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
			}
			if (count == 21)
			{
				for (int i = 0; i < 10; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle((-PI / 2.0f) + angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
			}
			if (count == 39)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Shame:
		if (mode == Mode::Easy)
		{
			if (count <= 4)
			{
				for (int i = 0 + bulletCount; i <= 2 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetAngle(PI);
						vecMissiles[i]->SetIsFire(true);
					}
					if (vecMissiles[i]->GetIsFire() == true)
					{
						if (vecMissiles[i]->GetPos().x <= (WINSIZE_X / 2) - 250.0f)
						{
							vecMissiles[i]->SetSpeed(1800.0f);
							destAngle1 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
							if (i == 0 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
							}
							if (i == 1 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
							}
							if (i == 2 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
							}
						}
					}
				}
				for (int i = 3 + bulletCount; i <= 5 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetAngle(2 * PI);
						vecMissiles[i]->SetIsFire(true);
					}
					if (vecMissiles[i]->GetIsFire() == true)
					{
						if (vecMissiles[i]->GetPos().x >= (WINSIZE_X / 2) + 250.0f)
						{
							vecMissiles[i]->SetSpeed(1800.0f);
							destAngle2 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
							if (i == 3 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
							}
							if (i == 4 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
							}
							if (i == 5 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
							}
						}
					}
				}
			}
			if (count == 4)
			{
				for (int i = 6 + bulletCount; i <= 11 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i == 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.5f);
						}
						if (i == 7 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.3f);
						}
						if (i == 8 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.1f);
						}
						if (i == 9 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.1f);
						}
						if (i == 10 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.3f);
						}
						if (i == 11 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.5f);
						}
						vecMissiles[i]->SetSpeed(1600.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
				bulletCount += 12;
			}
			if (bulletCount >= 180)
			{
				bulletCount = 0;
			}
			if (count >= 10)
			{
				count = 0;;
			}
		}
		else if (mode == Mode::Hard)
		{
			if (count <= 4)
			{
				for (int i = 0 + bulletCount; i <= 2 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetAngle(PI);
						vecMissiles[i]->SetIsFire(true);
					}
					if (vecMissiles[i]->GetIsFire() == true)
					{
						if (vecMissiles[i]->GetPos().x <= (WINSIZE_X / 2) - 250.0f)
						{
							vecMissiles[i]->SetSpeed(1800.0f);
							destAngle1 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
							if (i == 0 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
							}
							if (i == 1 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
							}
							if (i == 2 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
							}
						}
					}
				}
				for (int i = 3 + bulletCount; i <= 5 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetAngle(2 * PI);
						vecMissiles[i]->SetIsFire(true);
					}
					if (vecMissiles[i]->GetIsFire() == true)
					{
						if (vecMissiles[i]->GetPos().x >= (WINSIZE_X / 2) + 250.0f)
						{
							vecMissiles[i]->SetSpeed(1800.0f);
							destAngle2 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
							if (i == 3 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
							}
							if (i == 4 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
							}
							if (i == 5 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
							}
						}
					}
				}
			}
			if (count == 2)
			{
				for (int i = 6 + bulletCount; i <= 11 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i == 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.5f);
						}
						if (i == 7 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.3f);
						}
						if (i == 8 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.1f);
						}
						if (i == 9 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.1f);
						}
						if (i == 10 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.3f);
						}
						if (i == 11 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.5f);
						}
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			if (count == 3)
			{
				for (int i = 12 + bulletCount; i <= 16 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetAngle(destAngle + ((i - 14 - bulletCount) / 6.0f));
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
				
			}
			if (count == 4)
			{
				for (int i = 17 + bulletCount; i <= 22 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i == 17 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 20 - bulletCount) / 40.0f) - 0.5f);
						}
						if (i == 18 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 20 - bulletCount) / 40.0f) - 0.3f);
						}
						if (i == 19 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 20 - bulletCount) / 40.0f) - 0.1f);
						}
						if (i == 20 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 20 - bulletCount) / 40.0f) + 0.1f);
						}
						if (i == 21 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 20 - bulletCount) / 40.0f) + 0.3f);
						}
						if (i == 22 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 20 - bulletCount) / 40.0f) + 0.5f);
						}
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
				bulletCount += 23;
			}
			if (bulletCount >= 276)
			{
				bulletCount = 0;
			}
			if (count >= 10)
			{
				count = 0;;
			}
		}
		break;
	case Frustration:
		if (mode == Mode::Easy)
		{
			for (int i = 0; i < 1; i++)
			{
				for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
				{
					if ((*itMissiles)->GetIsFire() == false)
					{
						(*itMissiles)->SetPos(pos);
						(*itMissiles)->SetAngle(-PI/2.0f);
						(*itMissiles)->SetSpeed(1300);
						(*itMissiles)->SetIsFire(true);
						(*itMissiles)->SetIsLeftAngle(true);
						(*itMissiles)->SetLeftAddAngle(RadianToDegree(1), 80.0f);
						break;
					}
				}
			}
		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Jealousy:
		if (mode == Mode::Easy)
		{
			if (count <= 3)
			{
				for (int i = 0 + bulletCount; i < 3 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1200.0f);
						vecMissiles[i]->SetAngle(PI);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
						vecMissiles[i]->SetDisappears(4.0f);
					}
					if (vecMissiles[i]->GetIsFire() == true)
					{
						if (vecMissiles[i]->GetPos().x <= (WINSIZE_X / 2) - 250.0f)
						{
							vecMissiles[i]->SetSpeed(1800.0f);
							destAngle1 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
							if (i == 0 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI / 4);
							}
							if (i == 1 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI / 2);
							}
							if (i == 2 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
							}
						}
					}
				}
				for (int i = 3 + +bulletCount; i < 6 + +bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1200.0f);
						vecMissiles[i]->SetAngle(2 * PI);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
						vecMissiles[i]->SetDisappears(4.0f);
					}
					if (vecMissiles[i]->GetIsFire() == true)
					{
						if (vecMissiles[i]->GetPos().x >= (WINSIZE_X / 2) + 250.0f)
						{
							vecMissiles[i]->SetSpeed(1800.0f);
							destAngle2 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
							if (i == 3 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI / 4);
							}
							if (i == 4 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI / 2);
							}
							if (i == 5 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
							}
						}
					}
				}

			}
			if (count == 3)
			{
				for (int i = 6 + bulletCount; i < 10 + bulletCount; i += 1)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i == 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI / 4);
						}
						if (i == 7 + bulletCount)
						{
							vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
						}
						if (i == 8 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI + (PI / 4));
						}
						if (i == 9 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
						}
						vecMissiles[i]->SetSpeed(1800.0f);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
						vecMissiles[i]->SetDisappears(4.0f);
					}
				}

				bulletCount += 10;
			}
			if (bulletCount >= 280)
			{
				bulletCount = 0;
			}
			if (count >= 10)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
		if (count <= 3)
		{
			for (int i = 0 + bulletCount; i < 3 + bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetSpeed(1200.0f);
					vecMissiles[i]->SetAngle(PI);
					vecMissiles[i]->SetIsFire(true);
					vecMissiles[i]->SetIsPingPong(true);
					vecMissiles[i]->SetDisappears(4.0f);
				}
				if (vecMissiles[i]->GetIsFire() == true)
				{
					if (vecMissiles[i]->GetPos().x <= (WINSIZE_X / 2) - 250.0f)
					{
						vecMissiles[i]->SetSpeed(1200.0f);
						destAngle1 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
						if (i == 0 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI / 2);
						}
						if (i == 1 + bulletCount)
						{
							vecMissiles[i]->SetAngle((PI / 2) + (PI / 6));
						}
						if (i == 2 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI - (PI / 6));
						}
					}
				}
			}
			for (int i = 3 + +bulletCount; i < 6 + +bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetSpeed(1200.0f);
					vecMissiles[i]->SetAngle(2 * PI);
					vecMissiles[i]->SetIsFire(true);
					vecMissiles[i]->SetIsPingPong(true);
					vecMissiles[i]->SetDisappears(4.0f);
				}
				if (vecMissiles[i]->GetIsFire() == true)
				{
					if (vecMissiles[i]->GetPos().x >= (WINSIZE_X / 2) + 250.0f)
					{
						vecMissiles[i]->SetSpeed(1200.0f);
						destAngle2 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
						if (i == 3 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI / 2);
						}
						if (i == 4 + bulletCount)
						{
							vecMissiles[i]->SetAngle((PI / 2) - (PI / 6));
						}
						if (i == 5 + bulletCount)
						{
							vecMissiles[i]->SetAngle(0 + (PI / 6));
						}
					}
				}
			}

		}
		if (count == 3)
		{
			for (int i = 6 + bulletCount; i < 10 + bulletCount; i += 1)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					if (i == 6 + bulletCount)
					{
						vecMissiles[i]->SetAngle(PI / 4);
					}
					if (i == 7 + bulletCount)
					{
						vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
					}
					if (i == 8 + bulletCount)
					{
						vecMissiles[i]->SetAngle(PI + (PI / 4));
					}
					if (i == 9 + bulletCount)
					{
						vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
					}
					vecMissiles[i]->SetSpeed(1200.0f);
					vecMissiles[i]->SetIsFire(true);
					vecMissiles[i]->SetIsPingPong(true);
					vecMissiles[i]->SetDisappears(4.0f);
				}
			}

			bulletCount += 10;
		}
		if (bulletCount >= 280)
		{
			bulletCount = 0;
		}
		if (count >= 6)
		{
			count = 0;
		}
		}
		break;
	case Hoplessness:
		if (mode == Mode::Easy)
		{

		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Anger:
		if (mode == Mode::Easy)
		{
			if (life > 15)
			{
				if (count == 1)
				{
					for (int i = 0 + bulletCount; i < 42 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 20) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1300.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = true;
						}
					}
				}
				if (count == 2)
				{
					isShake = false;
				}
				if (count == 5)
				{
					for (int i = 42 + bulletCount; i < 51 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos1);
							if (i == 42 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 36));
							}
							if (i == 43 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 12));
							}
							if (i == 44 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 7.2));
							}
							if (i == 45 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - DegreeToRadian(35));
							}
							if (i == 46 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 4));
							}
							if (i == 47 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + DegreeToRadian(35));
							}
							if (i == 48 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 7.2));
							}
							if (i == 49 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 12));
							}
							if (i == 50 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 36));
							}
							vecMissiles[i]->SetSpeed(1300.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = true;
						}
					}
				}
				if (count == 6)
				{
					isShake = false;
				}
				if (count == 9)
				{
					for (int i = 51 + bulletCount; i < 60 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos2);
							if (i == 51 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 36));
							}
							if (i == 52 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 12));
							}
							if (i == 53 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 7.2));
							}
							if (i == 54 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + DegreeToRadian(35));
							}
							if (i == 55 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 4));
							}
							if (i == 56 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - DegreeToRadian(35));
							}
							if (i == 57 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 7.2));
							}
							if (i == 58 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 12));
							}
							if (i == 59 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 36));
							}
							vecMissiles[i]->SetSpeed(1300.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = true;
						}
					}
				}
				if (count == 10)
				{
					isShake = false;
				}
				bulletCount += 60;
				if(bulletCount >= 240)
				{
					bulletCount = 0;
				}
				if (count >= 15)
				{
					count = 3;
				}
			}
			if (life <= 15)
			{
				if (count != 0 && life <= 10 && isPattern == false)
				{
					count = 0;
					isPattern = true;
				}
				if (isPattern == true)
				{
					if (count == 4)
					{
						for (int i = 0 + bulletCount; i < 8 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle - (PI / 4) * (i - bulletCount));
								vecMissiles[i]->SetSpeed(1300.0f);
								vecMissiles[i]->SetIsFire(true);
							}
						}
					}
				}
				bulletCount += 8;
				if (bulletCount >= 288)
				{
					bulletCount = 0;
				}
				if (count >= 8)
				{
					count = 0;
				}
			}
		}
		else if (mode == Mode::Hard)
		{
			if (life > 20)
			{
				if (count == 1)
				{
					for (int i = 0 + bulletCount; i < 40 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 20) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1300.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = true;
						}
					}
				}
				if (count == 2)
				{
					isShake = false;
				}
				// 왼쪽 꼭지점 발사
				if (count == 5)
				{
					for (int i = 40 + bulletCount; i < 44 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos1);
							if (i == 40 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 10));
							}
							if (i == 41 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 5));
							}
							if (i == 42 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 5));
							}
							if (i == 43 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 10));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = true;
						}
					}
				}
				if (count == 6)
				{
					for (int i = 44 + bulletCount; i < 49 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos1);
							if (i == 44 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 12));
							}
							if (i == 45 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 6));
							}
							if (i == 46 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 4));
							}
							if (i == 47 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 6));
							}
							if (i == 48 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 12));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = false;
						}
					}
				}
				if (count == 7)
				{
					for (int i = 49 + bulletCount; i < 53 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos1);
							if (i == 49 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 10));
							}
							if (i == 50 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 5));
							}
							if (i == 51 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 5));
							}
							if (i == 52 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 10));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				if (count == 8)
				{
					for (int i = 53 + bulletCount; i < 58 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos1);
							if (i == 53 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 12));
							}
							if (i == 54 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 6));
							}
							if (i == 55 + bulletCount)
							{
								vecMissiles[i]->SetAngle((2 * PI) - (PI / 4));
							}
							if (i == 56 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 6));
							}
							if (i == 57 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) + (PI / 12));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				// 오른쪽 꼭지점 발사
				if (count == 10)
				{
					for (int i = 58 + bulletCount; i < 62 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos2);
							if (i == 58 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 10));
							}
							if (i == 59 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 5));
							}
							if (i == 60 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 5));
							}
							if (i == 61 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 10));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = true;
						}
					}
				}
				if (count == 11)
				{
					for (int i = 62 + bulletCount; i < 67 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos2);
							if (i == 62 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 12));
							}
							if (i == 63 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 6));
							}
							if (i == 64 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 4));
							}
							if (i == 65 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 6));
							}
							if (i == 66 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 12));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
							isShake = false;
						}
					}
				}
				if (count == 12)
				{
					for (int i = 67 + bulletCount; i < 71 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos2);
							if (i == 67 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 10));
							}
							if (i == 68 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 5));
							}
							if (i == 69 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 5));
							}
							if (i == 70 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 10));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				if (count == 13)
				{
					for (int i = 71 + bulletCount; i < 76 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(vertexPos2);
							if (i == 71 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 12));
							}
							if (i == 72 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 6));
							}
							if (i == 73 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI) + (PI / 4));
							}
							if (i == 74 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 6));
							}
							if (i == 75 + bulletCount)
							{
								vecMissiles[i]->SetAngle((-PI / 2) - (PI / 12));
							}
							vecMissiles[i]->SetSpeed(1100.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				bulletCount += 76;
				if (bulletCount >= 152)
				{
					bulletCount = 0;
				}
				if (count >= 18)
				{
					count = 3;
				}
			}
			// 2페이즈
			if (life <= 20)
			{
				if (count != 0 && life <= 10 && isPattern == false)
				{
					count = 0;
					isPattern = true;
				}
				if (isPattern == true)
				{
					if (count == 4)
					{
						for (int i = 0 + bulletCount; i < 16 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle - (PI / 8) * (i - bulletCount));
								vecMissiles[i]->SetSpeed(1100.0f);
								vecMissiles[i]->SetIsFire(true);
							}
						}
					}
					if (count == 5)
					{
						for (int i = 16 + bulletCount; i < 32 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle - (PI / 8) * (i - bulletCount) + (PI / 16));
								vecMissiles[i]->SetSpeed(1100.0f);
								vecMissiles[i]->SetIsFire(true);
							}
						}
					}
				}
				// 3페이즈
				if (life <= 10)
				{
					if (count == 2)
					{
						for (int i = 32 + bulletCount; i < 33 + bulletCount; i++)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(destAngle);
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
					if (count == 4)
					{
						for (int i = 33 + bulletCount; i < 35 + bulletCount; i++)
						{
							vecMissiles[i]->SetPos(pos);
							if (i == 33 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle + ((i - 34 - bulletCount) / 40.0f) - 0.1f);
							}
							if (i == 34 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle + ((i - 33 - bulletCount) / 40.0f) + 0.1f);
							}
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				bulletCount += 35;
				if (bulletCount >= 245)
				{
					bulletCount = 0;
				}
				if (count >= 8)
				{
					count = 0;
				}
			}
		}
		break;
	case Anxiety:
		if (mode == Mode::Easy)
		{

		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Sadness:
		if (mode == Mode::Easy)
		{
			if (life > 15)
			{
				if (count == 1)
				{
					for (int i = 0 + bulletCount; i < 15 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(110), 8.0f);
						}
					}
				}
				if (count == 2)
				{
					for (int i = 15 + bulletCount; i < 30 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(110), 8.0f);
						}
					}
				}
				if (count == 3)
				{
					for (int i = 30 + bulletCount; i < 45 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				if (count == 4)
				{
					for (int i = 45 + bulletCount; i < 60 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(110), 8.0f);
						}
					}
				}
				if (count == 5)
				{
					for (int i = 60 + bulletCount; i < 75 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(110), 8.0f);
						}
					}
				}
				if (count == 6)
				{
					for (int i = 75 + bulletCount; i < 90 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				if (count == 7)
				{
					for (int i = 90 + bulletCount; i < 105 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(110), 8.0f);
						}
					}
				}
				bulletCount += 105;
				if (bulletCount >= 210)
				{
					bulletCount = 0;
				}
				if (count >= 13)
				{
					count = 0;
				}
			}
			else if (life <= 15)
			{
				if (count == 1)
				{
					for (int i = 0 + bulletCount; i < 15 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(90), 8.5f);
						}
					}
				}
				if (count == 1)
				{
					for (int i = 15 + bulletCount; i < 30 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(90), 8.5f);
						}
					}
				}
				if (count == 4)
				{
					for (int i = 30 + bulletCount; i < 45 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(90), 8.5f);
						}
					}
				}
				if (count == 4)
				{
					for (int i = 45 + bulletCount; i < 60 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(90), 8.5f);
						}
					}
				}
				bulletCount += 60;
				if (bulletCount >= 180)
				{
					bulletCount = 0;
				}
				if (count >= 7)
				{
					count = 0;
				}
			}
		}
		else if (mode == Mode::Hard)
		{
			if (life > 20)
			{
				if (count == 1)
				{
					for (int i = 0 + bulletCount; i < 15 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1000.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(90), 15.0f);
						}
					}
				}
				if (count == 2)
				{
					for (int i = 15 + bulletCount; i < 30 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1000.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(90), 15.0f);
						}
					}
				}
				if (count == 3)
				{
					for (int i = 30 + bulletCount; i < 45 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1000.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(false);
						}
					}
				}
				if (count == 4)
				{
					for (int i = 45 + bulletCount; i < 60 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1000.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(90), 15.0f);
						}
					}
				}
				if (count == 5)
				{
					for (int i = 60 + bulletCount; i < 75 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1000.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(90), 15.0f);
						}
					}
				}
				if (count == 6)
				{
					for (int i = 75 + bulletCount; i < 105 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 15) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(1000.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(false);
						}
					}
				}
				bulletCount += 105;
				if (bulletCount >= 210)
				{
					bulletCount = 0;
				}
				if (count >= 10)
				{
					count = 0;
				}
			}
			if (life > 10 && life <= 20)
			{
				if (count != 0 && life <= 20 && isPattern == false)
				{
					count = 0;
					isPattern = true;
				}
				if (count == 3)
				{
					for (int i = 0 + bulletCount; i < 15 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(110), 15.0f);
						}
					}
				}
				if (count == 3)
				{
					for (int i = 15 + bulletCount; i < 30 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(110), 15.0f);
						}
					}
				}
				if (count == 4)
				{
					for (int i = 30 + bulletCount; i < 45 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(110), 15.0f);
						}
					}
				}
				if (count == 4)
				{
					for (int i = 45 + bulletCount; i < 60 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(110), 15.0f);
						}
					}
				}
				if (count == 5)
				{
					for (int i = 60 + bulletCount; i < 75 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle + (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(true);
							vecMissiles[i]->SetRightAddAngle(DegreeToRadian(110), 15.0f);
						}
					}
				}
				if (count == 5)
				{
					for (int i = 75 + bulletCount; i < 90 + bulletCount; i++)
					{
						if (vecMissiles[i]->GetIsFire() == false)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(angle - (PI / 7) * (i - bulletCount));
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(true);
							vecMissiles[i]->SetIsRightAngle(false);
							vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(110), 15.0f);
						}
					}
				}
				bulletCount += 90;
				if (bulletCount >= 360)
				{
					bulletCount = 0;
				}
				if (count >= 6)
				{
					count = 1;
				}

			}
			if (life <= 10)
			{
				if (count != 0 && life <= 10 && isPattern == true)
				{
					count = 0;
					isPattern = false;
				}
				if (isPattern == false)
				{
					if (count == 2)
					{
						for (int i = 0 + bulletCount; i < 30 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle + (PI / 15) * (i - bulletCount));
								vecMissiles[i]->SetSpeed(900.0f);
								vecMissiles[i]->SetIsFire(true);
								vecMissiles[i]->SetIsLeftAngle(false);
								vecMissiles[i]->SetIsRightAngle(true);
								vecMissiles[i]->SetRightAddAngle(DegreeToRadian(80), 8.0f);
							}
						}
					}
					if (count == 3)
					{
						for (int i = 30 + bulletCount; i < 60 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle - (PI / 15) * (i - bulletCount));
								vecMissiles[i]->SetSpeed(900.0f);
								vecMissiles[i]->SetIsFire(true);
								vecMissiles[i]->SetIsLeftAngle(true);
								vecMissiles[i]->SetIsRightAngle(false);
								vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(80), 8.0f);
							}
						}
					}
					if (count == 4)
					{
						for (int i = 60 + bulletCount; i < 96 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(0 - (PI / 18) * (i - bulletCount));
								vecMissiles[i]->SetSpeed(900.0f);
								vecMissiles[i]->SetIsFire(true);
								vecMissiles[i]->SetIsLeftAngle(false);
								vecMissiles[i]->SetIsRightAngle(false);
							}
						}
					}
					if (count == 5)
					{
						for (int i = 96 + bulletCount; i < 126 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle + (PI / 15) * (i - bulletCount));
								vecMissiles[i]->SetSpeed(900.0f);
								vecMissiles[i]->SetIsFire(true);
								vecMissiles[i]->SetIsLeftAngle(false);
								vecMissiles[i]->SetIsRightAngle(true);
								vecMissiles[i]->SetRightAddAngle(DegreeToRadian(80), 8.0f);
							}
						}
					}
					if (count == 6)
					{
						for (int i = 126 + bulletCount; i < 156 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle - (PI / 15) * (i - bulletCount));
								vecMissiles[i]->SetSpeed(900.0f);
								vecMissiles[i]->SetIsFire(true);
								vecMissiles[i]->SetIsLeftAngle(true);
								vecMissiles[i]->SetIsRightAngle(false);
								vecMissiles[i]->SetLeftAddAngle(-DegreeToRadian(80), 8.0f);
							}
						}
					}
					bulletCount += 150;
					if (bulletCount >= 200)
					{
						bulletCount = 0;
					}
					if (count >= 9)
					{
						count = 0;
					}
				}
			}
		}
		break;
	case Panic:
		if (mode == Mode::Easy)
		{

		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Despair:
		if (mode == Mode::Easy)
		{

		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case END_NUM:
		break;
	default:
		break;
	}
}
