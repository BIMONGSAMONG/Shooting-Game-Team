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
	random = 0;
	life = 0;
	clearBullet = false;
	phaseTwo = false;
	lastPhase = false;
	randomAngle = 0.0f;
	randomSpeed = 0.0f;
	randomPhase = 0;
	randomAddAngle = 0;
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

void EMissileManager::Update(EnemyName name, FPOINT pos, float destAngle, float fireDelay, Mode mode, FPOINT rotatePos1, FPOINT rotatePos2)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Update(targetPos);
	}

	fireTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (fireTime >= fireDelay)
	{
		if (isShoot)
		{
			Fire(name, pos, destAngle, mode, rotatePos1, rotatePos2);
		}
		count++;
		fireTime = 0.0f;
		randomPos.x = rand() % WINSIZE_X + 1;
		random = rand() % 3 + 1;
		randomSpeed = rand() % 500 + 0;
		randomPhase = rand() % 4;
		if (isShoot == false)
		{
			isShake = false;
		}
	}

	if (name == EnemyName::Despair)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetPos().x < -16 || (*itMissiles)->GetPos().x > WINSIZE_X + 16 ||
				(*itMissiles)->GetPos().y < -16 || (*itMissiles)->GetPos().y > WINSIZE_Y + 16)
			{
				(*itMissiles)->SetIsFire(false);
				(*itMissiles)->SetIsLeftAngle(false);
				(*itMissiles)->SetIsRightAngle(false);
			}
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

void EMissileManager::Fire(EnemyName name, FPOINT pos, float destAngle, Mode mode, FPOINT rotatePos1, FPOINT rotatePos2)
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
			if (count == 1)
			{
				for (int i = -2; i < 3; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(destAngle + i * DegreeToRadian(5));
							(*itMissiles)->SetSpeed(0.0f);
							(*itMissiles)->SetIsFire(true);
							if (i == -2)
							{
								(*itMissiles)->SetC_Speed(true, 0.12, 900.f, 0);
							}
							if (i == -1)
							{
								(*itMissiles)->SetC_Speed(true, 0.06, 900.f, 0);
							}
							if (i == 0)
							{
								(*itMissiles)->SetC_Speed(true, 0.0, 900.f, 0);
							}
							if (i == 1)
							{
								(*itMissiles)->SetC_Speed(true, 0.06, 900.f, 0);
							}
							if (i == 2)
							{
								(*itMissiles)->SetC_Speed(true, 0.12, 900.f, 0);
							}
							break;
						}
					}
				}
			}
		}
		if (count == 2)
			count = 0;

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
			bulletCount += 6;
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
			if (count == 1)
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
			if (count > 0)
			{
				for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
				{
					if ((*itMissiles)->GetIsFire() == false)
					{
						(*itMissiles)->SetPos(randomPos = { randomPos.x - 200, 0 });
						(*itMissiles)->SetAngle(DegreeToRadian(-70));
						(*itMissiles)->SetSpeed(1200);
						(*itMissiles)->SetIsFire(true);
						break;
					}
				}
				for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
				{
					if ((*itMissiles)->GetIsFire() == false)
					{
						(*itMissiles)->SetPos(randomPos = { randomPos.x + 200, 0 });
						(*itMissiles)->SetAngle(DegreeToRadian(-110));
						(*itMissiles)->SetSpeed(1200);
						(*itMissiles)->SetIsFire(true);
						break;
					}
				}
			}
			if (count == 5)
			{
				count = 1;
			}
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
						if (i <= 2 + bulletCount)
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
			if (count == 1)
			{

				for (int i = 0; i < 12; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
							(*itMissiles)->SetSpeed(850.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(false);
							(*itMissiles)->SetIsRightAngle(true);
							(*itMissiles)->SetRightAddAngle(DegreeToRadian(76), 12.0f);
							break;
						}
					}
				}

			}
			if (count == 2)
			{
				for (int i = 0; i < 12; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
							(*itMissiles)->SetSpeed(850.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(76), 12.0f);
							break;
						}
					}
				}
			}
			if (count == 3)
			{
				for (int i = 0; i < 12; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
							(*itMissiles)->SetSpeed(850.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(false);
							(*itMissiles)->SetIsRightAngle(true);
							(*itMissiles)->SetRightAddAngle(DegreeToRadian(76), 12.0f);
							break;
						}
					}
				}

			}
			if (count == 4)
			{
				for (int i = 0; i < 12; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
							(*itMissiles)->SetSpeed(850.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(76), 12.0f);
							break;
						}
					}
				}
			}
			if (count == 6)
			{
				count = 0;
			}
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
			if (count == 1)
			{
				angle = DegreeToRadian(18);
				for (int i = 0; i < 20; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(-PI / 2.0f + angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							//(*itMissiles)->SetIsSizeDown(true);
							//(*itMissiles)->SetIsSize(15);
							break;
						}
					}
				}
			}
			if (count == 3)
			{
				for (int i = 0; i < 20; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle((-PI / 4.0f) + angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							//(*itMissiles)->SetIsSizeUp(true);
							//(*itMissiles)->SetIsSize(10);
							break;
						}
					}
				}
			}
			if (count == 8)
			{
				for (int i = 0; i < 20; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(-PI / 2.0f + angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							//(*itMissiles)->SetIsSizeUp(true);
							//(*itMissiles)->SetIsSize(10);
							break;
						}
					}
				}
			}
			if (count == 10)
			{
				for (int i = 0; i < 20; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle((-PI / 4.0f) + angle * i);
							(*itMissiles)->SetSpeed(1500.0f);
							(*itMissiles)->SetIsFire(true);
							//(*itMissiles)->SetIsSizeDown(true);
							//(*itMissiles)->SetIsSize(15);
							break;
						}
					}
				}
			}
			if (count == 15)
			{
				count = 0;
			}
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
							vecMissiles[i]->SetSpeed(1300.0f);
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
							vecMissiles[i]->SetSpeed(1300.0f);
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
						vecMissiles[i]->SetSpeed(1400.0f);
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
							vecMissiles[i]->SetSpeed(1400.0f);
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
							vecMissiles[i]->SetSpeed(1400.0f);
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
						vecMissiles[i]->SetSpeed(1250.0f);
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
						vecMissiles[i]->SetSpeed(1250.0f);
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
						vecMissiles[i]->SetSpeed(1250.0f);
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
			if (count == 1)
			{
				for (int i = 0; i < 9; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(-PI);
							(*itMissiles)->SetSpeed(0.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(35.0f + i * 5.8f, 150.0f + i * 25.0f);
							(*itMissiles)->SetC_Speed(true, i * 0.18, 950.0f, 0);
							break;
						}
					}
				}
			}
			if (count == 35)
			{
				for (int i = 0; i < 9; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(0);
							(*itMissiles)->SetSpeed(0.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsRightAngle(true);
							(*itMissiles)->SetIsLeftAngle(false);
							(*itMissiles)->SetRightAddAngle(-35.0f - i * 5.8f, 150.0f + i * 25.0f);
							(*itMissiles)->SetC_Speed(true, i * 0.18, 950.0f, 0);
							break;
						}
					}
				}
			}
			if (count == 70)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{

			if (count == 1)
			{
				for (int i = 0; i < 5; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(-PI);
							(*itMissiles)->SetSpeed(0.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(64.8f + i * 5.8f, 200.0f);
							(*itMissiles)->SetC_Speed(true, i * 0.12, 950.0f, 0);
							(*itMissiles)->SetRevers(1.5f + i * 0.1, 2.0f, true, true, 5.0f);
							break;
						}
					}
				}
			}
			if (count == 10 || count == 24)
			{
				for (int i = 0; i < 15; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(DegreeToRadian(24)*i);
							(*itMissiles)->SetSpeed(850.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(45.0f, 225.f);
							//(*itMissiles)->SetC_Speed(true, 0.0, 200.0f, 0);
							(*itMissiles)->SetRevers(0.0f, 1.2f, true, true, 4.0f);
							break;
						}
					}
				}
				for (int i = 0; i < 15; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(DegreeToRadian(24) * i);
							(*itMissiles)->SetSpeed(850.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(-45.0f, 225.f);
							//(*itMissiles)->SetC_Speed(true, 0.0, 200.0f, 0);
							(*itMissiles)->SetRevers(0.0f, 1.2f, true, true, 4.0f);
							break;
						}
					}
				}
			}
			if (count == 15)
			{
				for (int i = 0; i < 5; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(0);
							(*itMissiles)->SetSpeed(0.0f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetIsLeftAngle(true);
							(*itMissiles)->SetIsRightAngle(false);
							(*itMissiles)->SetLeftAddAngle(-64.8f - i * 5.8f, 200.0f);
							(*itMissiles)->SetC_Speed(true, i * 0.12, 950.0f, 0);
							(*itMissiles)->SetRevers(1.5f + i * 0.1, 2.0f, true, true, 5.0f);
							break;
						}
					}
				}

			}
			if (count == 50)
			{
				count = 0;
			}
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
			if (count % 3 == 0)
			{
				angle += DegreeToRadian(10);
				for (int i = 0; i < 12; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(DegreeToRadian(30) * i + angle);
							(*itMissiles)->SetSpeed(650.f);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
			}
			if (count == 9)
			{
				for (int i = 0; i < 6; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos = { WINSIZE_X / 2.0 - 250.0f, 0 });
							(*itMissiles)->SetAngle(-PI / 2.0);
							(*itMissiles)->SetSpeed(600.f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetC_Angle(true, random - 0.5, angle + DegreeToRadian(60) * i);
							break;
						}
					}
				}
				random = rand() % 3 + 1;
			}
			if (count == 18)
			{
				for (int i = 0; i < 6; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos = { WINSIZE_X / 2.0 + 250.0f, 0 });
							(*itMissiles)->SetAngle(-PI / 2.0);
							(*itMissiles)->SetSpeed(600.f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetC_Angle(true, random - 0.5, angle + DegreeToRadian(60) * i);
							break;
						}
					}
				}
			}
			if (count == 18)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			if (count % 2 == 0)
			{
				angle += DegreeToRadian(10);
				for (int i = 0; i < 16; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(DegreeToRadian(22.5) * i + angle);
							(*itMissiles)->SetSpeed(650.f);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
			}
			if (count % 7 == 0 || count == 18)
			{
				for (int i = 0; i < 6; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos = { WINSIZE_X / 2.0 - 250.0f, 0 });
							(*itMissiles)->SetAngle(-PI / 2.0);
							(*itMissiles)->SetSpeed(850.f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetC_Angle(true, random - 0.8, angle + DegreeToRadian(60) * i);
							break;
						}
					}
				}
				random = rand() % 3 + 1;
			}
			if (count % 9 == 0 || count == 18)
			{
				for (int i = 0; i < 6; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos = { WINSIZE_X / 2.0 + 250.0f, 0 });
							(*itMissiles)->SetAngle(-PI / 2.0);
							(*itMissiles)->SetSpeed(850.f);
							(*itMissiles)->SetIsFire(true);
							(*itMissiles)->SetC_Angle(true, random - 0.8, angle + DegreeToRadian(60) * i);
							break;
						}
					}
				}
			}
			if (count == 18)
			{
				count = 0;
			}
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
								vecMissiles[i]->SetAngle((PI)+(PI / 36));
							}
							if (i == 52 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 12));
							}
							if (i == 53 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 7.2));
							}
							if (i == 54 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+DegreeToRadian(35));
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
				if (bulletCount >= 300)
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
				isShake = false;
				if (count != 0 && life <= 15 && isPattern == false)
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
								vecMissiles[i]->SetAngle((PI)+(PI / 10));
							}
							if (i == 59 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 5));
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
								vecMissiles[i]->SetAngle((PI)+(PI / 12));
							}
							if (i == 63 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 6));
							}
							if (i == 64 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 4));
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
								vecMissiles[i]->SetAngle((PI)+(PI / 10));
							}
							if (i == 68 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 5));
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
								vecMissiles[i]->SetAngle((PI)+(PI / 12));
							}
							if (i == 72 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 6));
							}
							if (i == 73 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI)+(PI / 4));
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
				isShake = false;
				if (count != 0 && life <= 20 && isPattern == false)
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
					if (count == 4)
					{
						for (int i = 16 + bulletCount; i < 32 + bulletCount; i++)
						{
							if (vecMissiles[i]->GetIsFire() == false)
							{
								vecMissiles[i]->SetPos(pos);
								vecMissiles[i]->SetAngle(angle - (PI / 8) * (i - bulletCount) + (PI / 16));
								vecMissiles[i]->SetSpeed(800.0f);
								vecMissiles[i]->SetIsFire(true);
							}
						}
					}
				}
				// 3페이즈
				if (life <= 10)
				{
					isShake = false;
					if (count == 1)
					{
						for (int i = 32 + bulletCount; i < 33 + bulletCount; i++)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(destAngle);
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
					if (count == 2)
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
					if (count == 3)
					{
						for (int i = 35 + bulletCount; i < 36 + bulletCount; i++)
						{
							vecMissiles[i]->SetPos(pos);
							vecMissiles[i]->SetAngle(destAngle);
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
					if (count == 4)
					{
						for (int i = 36 + bulletCount; i < 38 + bulletCount; i++)
						{
							vecMissiles[i]->SetPos(pos);
							if (i == 36 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle + ((i - 37 - bulletCount) / 40.0f) - 0.1f);
							}
							if (i == 37 + bulletCount)
							{
								vecMissiles[i]->SetAngle(destAngle + ((i - 36 - bulletCount) / 40.0f) + 0.1f);
							}
							vecMissiles[i]->SetSpeed(900.0f);
							vecMissiles[i]->SetIsFire(true);
						}
					}
				}
				bulletCount += 38;
				if (bulletCount >= 342)
				{
					bulletCount = 0;
				}
				if (count >= 5)
				{
					count = 0;
				}
			}
		}
		break;
	case Anxiety:
		if (mode == Mode::Easy)
		{
			if (life > 15)
			{
				if (count == 1)
				{
					for (int i = -1; i < 2; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(PI + i * DegreeToRadian(30));
								(*itMissiles)->SetSpeed(750.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsPingPong(true);
								break;
							}
						}
					}
					for (int i = -1; i < 2; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(0.0f + i * DegreeToRadian(30));
								(*itMissiles)->SetSpeed(750.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsPingPong(true);
								break;
							}
						}
					}
				}
				if (count == 6)
				{
					for (int i = 0; i < 3; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(PI / 2.0 - i * DegreeToRadian(45));
								(*itMissiles)->SetSpeed(750.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsPingPong(true);
								break;
							}
						}
					}
					for (int i = 0; i < 3; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(-PI / 2.0 - i * DegreeToRadian(45));
								(*itMissiles)->SetSpeed(750.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsPingPong(true);
								break;
							}
						}
					}
				}

				if (count == 11)
				{
					for (int i = 0; i < 3; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(PI / 2.0 + i * DegreeToRadian(45));
								(*itMissiles)->SetSpeed(750.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsPingPong(true);
								break;
							}
						}
					}
					for (int i = 0; i < 3; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(-PI / 2.0 + i * DegreeToRadian(45));
								(*itMissiles)->SetSpeed(750.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsPingPong(true);
								break;
							}
						}
					}
				}
			}
			if (clearBullet == false)
			{
				if (life <= 15)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == true)
						{
							(*itMissiles)->SetIsFire(false);
							(*itMissiles)->SetIsPingPong(false);
						}
					}
					clearBullet = true;
				}
			}
			if (life <= 15)
			{
				if (phaseTwo == false)
				{
					count = 0;
					phaseTwo = true;
				}
				if (count % 12 == 0)
				{
					for (int i = 0; i < 6; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { 20 , 0 });
								(*itMissiles)->SetAngle(DegreeToRadian(-45));
								(*itMissiles)->SetSpeed(800.f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetDPingPingTime(1.5);
								(*itMissiles)->SetToPingPingTime(0.0f);
								(*itMissiles)->SetIsPingPong(true);
								(*itMissiles)->SetC_Angle(true, random - 0.8, DegreeToRadian(60) * i + angle);
								break;
							}
						}
					}
					random = rand() % 3 + 1;
					angle += DegreeToRadian(10);
				}
				if (count % 12 == 0)
				{
					for (int i = 0; i < 6; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { WINSIZE_X - 20 , 0 });
								(*itMissiles)->SetAngle(DegreeToRadian(-135));
								(*itMissiles)->SetSpeed(800.f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetDPingPingTime(1.5);
								(*itMissiles)->SetToPingPingTime(0.0f);
								(*itMissiles)->SetIsPingPong(true);
								(*itMissiles)->SetC_Angle(true, random - 0.8, DegreeToRadian(60) * i + angle);
								break;
							}
						}
					}
				}
			}

			if (count == 30)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			if (life > 20)
			{
				if (count == 1)
				{
					for (int i = 0; i < 7; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(PI + i * DegreeToRadian(4.5));
								(*itMissiles)->SetSpeed(1100.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);

								break;
							}
						}
					}
					for (int i = 0; i < 7; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(0 - i * DegreeToRadian(4.5));
								(*itMissiles)->SetSpeed(1100.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);

								break;
							}
						}
					}
				}

				if (count == 5)
				{
					count = 0;
				}
			}
			if (life <= 20 && life > 10)
			{
				if (phaseTwo == false)
				{
					count = 0;
					phaseTwo = true;
				}
				if (count == 1)
				{
					for (int i = 0; i < 11; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(PI - i * DegreeToRadian(4.5) + angle);
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);
								(*itMissiles)->SetC_Speed(true, i*0.09, 1100.f, 0.0f);
								break;
							}
						}
					}
					for (int i = 0; i < 11; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(0 - i * DegreeToRadian(4.5) + angle);
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);
								(*itMissiles)->SetC_Speed(true, i*0.09, 1100.f, 0.0f);
								break;
							}
						}
					}
				}
				if (count == 10)
				{
					count = 0;
					angle -= DegreeToRadian(35);
				}
			}
			if (life <= 10)
			{
				if (lastPhase == false)
				{
					count = 17;
					lastPhase = true;
					angle = 0.0;
				}
				if (count == 1)
				{
					for (int i = 0; i < 9; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(PI - i * DegreeToRadian(4.2) + angle);
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);
								(*itMissiles)->SetC_Speed(true, i*0.09, 1100.f, 0.0f);
								break;
							}
						}
					}
					for (int i = 0; i < 9; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(PI / 2.0f - i * DegreeToRadian(4.2) + angle);
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);
								(*itMissiles)->SetC_Speed(true, i*0.09, 1100.f, 0.0f);
								break;
							}
						}
					}
					for (int i = 0; i < 9; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(0 - i * DegreeToRadian(4.2) + angle);
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);
								(*itMissiles)->SetC_Speed(true, i*0.09, 1100.f, 0.0f);
								break;
							}
						}
					}
					for (int i = 0; i < 9; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(-PI / 2.0f - i * DegreeToRadian(4.2) + angle);
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLR_PingPong(true);
								(*itMissiles)->SetdLR_PingPong(3.5f);
								(*itMissiles)->SetC_Speed(true, i*0.09, 1100.f, 0.0f);
								break;
							}
						}
					}
				}
				if (count == 20)
				{
					count = 0;
					angle -= DegreeToRadian(60);
				}
			}
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
							vecMissiles[i]->SetSpeed(700.0f);
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
							vecMissiles[i]->SetSpeed(700.0f);
							vecMissiles[i]->SetIsFire(true);
							vecMissiles[i]->SetIsLeftAngle(false);
							vecMissiles[i]->SetIsRightAngle(false);
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
			if (life > 15)
			{
				for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
				{
					if ((*itMissiles)->GetIsFire() == false)
					{
						(*itMissiles)->SetPos(randomPos);
						(*itMissiles)->SetAngle(-PI / 2.0f);
						(*itMissiles)->SetSpeed(950);
						(*itMissiles)->SetIsFire(true);
						break;
					}
				}
				if (count == 2)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(randomPos);
							(*itMissiles)->SetAngle(-PI / 2.0f);
							(*itMissiles)->SetSpeed(950);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
				if (count == 3)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(randomPos);
							(*itMissiles)->SetAngle(-PI / 2.0f);
							(*itMissiles)->SetSpeed(950);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
				if (count == 3)
				{
					count = 0;
				}
			}
			else
			{
				if (phaseTwo == false)
				{
					count = 0;
					phaseTwo = true;
				}
				if (count == 1)
				{
					for (int i = 0; i < 8; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { 0,-30 });
								(*itMissiles)->SetAngle(DegreeToRadian(10.0) + -PI / 2.0f + i * DegreeToRadian(10.0));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-20.0f, 2500);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
					for (int i = 0; i < 8; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { WINSIZE_X,-30 });
								(*itMissiles)->SetAngle(-DegreeToRadian(10.0) + (-PI / 2.0f) - i * DegreeToRadian(10.0));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(+20.0f, 2500);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
				}
				if (count == 5)
				{
					for (int i = 0; i < 8; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { 0,-30 });
								(*itMissiles)->SetAngle(DegreeToRadian(10.0) + -PI / 2.0f + i * DegreeToRadian(10.0));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-25.0f, 2500);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
					for (int i = 0; i < 8; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { WINSIZE_X,-30 });
								(*itMissiles)->SetAngle(-DegreeToRadian(10.0) + (-PI / 2.0f) - i * DegreeToRadian(10.0));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(+25.0f, 2500);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
				}
				if (count == 10)
				{
					for (int i = -4; i < 5; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { 0,0 });
								(*itMissiles)->SetAngle(DegreeToRadian(-60) + i * DegreeToRadian(11.25));
								(*itMissiles)->SetSpeed(850.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetC_Speed(true, 0.2, 820.0f, 0);
								break;
							}
						}
					}
					for (int i = -4; i < 5; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { WINSIZE_X,0 });
								(*itMissiles)->SetAngle(DegreeToRadian(-120) + i * DegreeToRadian(11.25));
								(*itMissiles)->SetSpeed(850.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetC_Speed(true, 0.2, 820.0f, 0);
								break;
							}
						}
					}
				}
				if (count == 15)
				{
					count = 0;
				}
			}
		}
		else if (mode == Mode::Hard)
		{
			if (life > 20)
			{
				if (count % 1 == 0)
				{
					if (randomAngle != 0)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(randomPos);
								(*itMissiles)->SetAngle(randomAngle);
								(*itMissiles)->SetSpeed(950 + randomSpeed);
								(*itMissiles)->SetIsFire(true);
								break;
							}
						}
						randomPos.x = rand() % WINSIZE_X + 1;
					}
				}
				if (count == 2)
				{
					if (randomAngle != 0)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(randomPos);
								(*itMissiles)->SetAngle(randomAngle);
								(*itMissiles)->SetSpeed(950 + randomSpeed);
								(*itMissiles)->SetIsFire(true);
								break;
							}
						}
					}
				}
				if (count == 2)
				{
					count = 0;
					randomAngle = rand() % 4;
					if (randomAngle == 0)
					{
						randomAngle = DegreeToRadian(-80);
					}
					if (randomAngle == 1)
					{
						randomAngle = DegreeToRadian(-100);
					}
					if (randomAngle == 2)
					{

						randomAngle = DegreeToRadian(-85);
					}
					if (randomAngle == 3)
					{
						randomAngle = DegreeToRadian(-95);
					}
					randomPos.x = rand() % WINSIZE_X + 1;
				}
			}
			if (life <= 20 && life > 10)
			{
				if (phaseTwo == false)
				{
					count = 0;
					phaseTwo = true;
				}
				if (count == 1)
				{
					for (int i = 0; i < 14; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { 0,0 });
								(*itMissiles)->SetAngle(DegreeToRadian(4.285714285714286f) + -PI / 2.0f + i * DegreeToRadian(6.7));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-4.285714285714286f, 1000);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
					for (int i = 0; i < 14; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { WINSIZE_X,0 });
								(*itMissiles)->SetAngle(-DegreeToRadian(4.285714285714286f) + (-PI / 2.0f) - i * DegreeToRadian(6.7));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(+4.285714285714286f, 1000);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
				}
				if (count == 5)
				{
					for (int i = 0; i < 14; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { 0,0 });
								(*itMissiles)->SetAngle(DegreeToRadian(4.285714285714286f) + -PI / 2.0f + i * DegreeToRadian(6.7));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-4.285714285714286f, 1000);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
					for (int i = 0; i < 14; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { WINSIZE_X,0 });
								(*itMissiles)->SetAngle(-DegreeToRadian(4.285714285714286f) + (-PI / 2.0f) - i * DegreeToRadian(6.7));
								(*itMissiles)->SetSpeed(0.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(+4.285714285714286f, 1000);
								(*itMissiles)->SetC_Speed(true, i * 0.12, 820.0f, 0);
								break;
							}
						}
					}
				}
				if (count == 10)
				{
					for (int i = -5; i < 6; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { 0,0 });
								(*itMissiles)->SetAngle(DegreeToRadian(-60) + i * DegreeToRadian(9));
								(*itMissiles)->SetSpeed(820.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetC_Speed(true, 0.2, 820.0f, 830);
								break;
							}
						}
					}
					for (int i = -5; i < 6; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos = { WINSIZE_X,0 });
								(*itMissiles)->SetAngle(DegreeToRadian(-120) + i * DegreeToRadian(9));
								(*itMissiles)->SetSpeed(820.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetC_Speed(true, 0.2, 820.0f, 830);
								break;
							}
						}
					}
				}

				if (count == 15)
				{
					count = 0;
				}
			}
			if (life <= 10)
			{
				if (lastPhase == false)
				{
					lastPhase = true;
					count = 2;

				}
				FPOINT lastPos = { pos.x , pos.y - 50 };
				FPOINT lastPos2 = { pos.x , pos.y + 20 };

				FPOINT lastPos3 = { pos.x - 50 , pos.y };
				FPOINT lastPos4 = { pos.x + 20, pos.y };

				FPOINT lastPos5 = { pos.x , pos.y + 50 };
				FPOINT lastPos6 = { pos.x , pos.y - 20 };

				FPOINT lastPos7 = { pos.x + 50, pos.y };
				FPOINT lastPos8 = { pos.x - 20, pos.y };
				if (randomPhase == 0)
				{
					if (count == 1)
					{
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos);
									(*itMissiles)->SetAngle(0 + i * DegreeToRadian(11.25));
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos2);
									(*itMissiles)->SetAngle(DegreeToRadian(3.75) - i * DegreeToRadian(11.25));
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
					}
				}
				if (randomPhase == 1)
				{
					if (count == 1)
					{
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos3);
									(*itMissiles)->SetAngle(0 + i * DegreeToRadian(11.25));
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos4);
									(*itMissiles)->SetAngle(DegreeToRadian(3.75) - i * DegreeToRadian(11.25));
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
					}
				}
				if (randomPhase == 2)
				{
					if (count == 1)
					{
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos5);
									(*itMissiles)->SetAngle(0 - i * DegreeToRadian(11.25));
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos6);
									(*itMissiles)->SetAngle(DegreeToRadian(3.75) + i * DegreeToRadian(11.25));
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
					}
				}
				if (randomPhase == 3)
				{
					if (count == 1)
					{
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos7);
									(*itMissiles)->SetAngle(0 - i * DegreeToRadian(11.25) - angle);
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
						for (int i = 0; i < 32; i++)
						{
							for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
							{
								if ((*itMissiles)->GetIsFire() == false)
								{
									(*itMissiles)->SetPos(lastPos8);
									(*itMissiles)->SetAngle(DegreeToRadian(3.75) + i * DegreeToRadian(11.25) + angle);
									(*itMissiles)->SetSpeed(1200.0f);
									(*itMissiles)->SetIsFire(true);
									break;
								}
							}
						}
					}
				}
				if (count == 4)
				{
					count = 0;
					angle += DegreeToRadian(3.75);
				}
			}
		}
		break;
	case Despair:
		if (mode == Mode::Easy)
		{
			if (phase == Phase::Phase1)
			{
				randomAngle = rand() % 300;
				if (count == 1)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(76) + randomAngle / 180.f, 12.0f);
								break;
							}
						}
						randomAngle = rand() % 300;
					}
				}
				if (count == 2)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(76) - randomAngle / 180.f, 12.0f);
								break;
							}
						}
						randomAngle = rand() % 300;
					}
				}
				if (count == 3)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(76) + randomAngle / 180.f, 12.0f);
								break;
							}
						}
						randomAngle = rand() % 300;
					}

				}
				if (count == 4)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(76) - randomAngle / 180.f, 12.0f);
								break;
							}
						}
						randomAngle = rand() % 300;
					}
				}
				if (count == 8)
				{
					count = 0;
				}
			}
			if (phase == Phase::Phase2)
			{
				if (phaseTwo == false)
				{
					count = 1;
					phaseTwo = true;
					randomAngle = 0;
				}
				random = rand() % 5;
				randomAngle = rand() % 30;
				if (count == random || count == random - 1 || count == random + 1 || count == random - 2)
				{
					for (int i = 0; i < 24; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(0 + (i * DegreeToRadian(15) + DegreeToRadian(randomAngle)));
								(*itMissiles)->SetSpeed(900.0f);
								(*itMissiles)->SetIsFire(true);
								break;
							}
						}
					}
				}
				if (count >= 9)
				{
					count = 0;
				}
			}
			if (phase == Phase::Phase3)
			{
				if (lastPhase == false)
				{
					count = 0;
					lastPhase = true;
					randomAngle = 0;
					random = 0;
					bulletCount = 0;
				}
				if (bulletCount == 4)
				{
					
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
							if ((*itMissiles)->GetIsFire() == false)
							{
								if ((*itMissiles)->GetIsRotate() == false)
								{
									(*itMissiles)->SetPos(rotatePos1);
									(*itMissiles)->SetSpeed(600.0f);
									(*itMissiles)->SetIsFire(true);
									(*itMissiles)->SetRotate(4.5);
									(*itMissiles)->SetIsRotate(true);
									(*itMissiles)->SetXPlus(true);
								}
								break;
							}
					}
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							if ((*itMissiles)->GetIsRotate() == false)
							{
								(*itMissiles)->SetPos(rotatePos2);
								(*itMissiles)->SetSpeed(600.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetRotate(4.5);
								(*itMissiles)->SetIsRotate(true);
								(*itMissiles)->SetXPlus(false);
							}
							break;
						}
					}
				}
				if (bulletCount == 5)
				{
					bulletCount = 0;
				}
				if (bossLife > 20)
				{
					//if (count % 3 == 0)
					//{
					//	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					//	{
					//		if ((*itMissiles)->GetIsFire() == false)
					//		{
					//			(*itMissiles)->SetPos(randomPos);
					//			(*itMissiles)->SetAngle(-PI / 2.0f);
					//			(*itMissiles)->SetSpeed(1000.0f);
					//			(*itMissiles)->SetIsFire(true);
					//			(*itMissiles)->SetIsRotate(false);
					//			break;
					//		}
					//	}
					//}
					//if (count == 9)
					//{
					//	randomPos.x = rand() % WINSIZE_X + 1;
					//	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					//	{
					//		if ((*itMissiles)->GetIsFire() == false)
					//		{
					//			(*itMissiles)->SetPos(randomPos);
					//			(*itMissiles)->SetAngle(-PI / 2.0f);
					//			(*itMissiles)->SetSpeed(1000.0f);
					//			(*itMissiles)->SetIsFire(true);
					//			(*itMissiles)->SetIsRotate(false);
					//			break;
					//		}
					//	}
					//}
				}
				else if (bossLife <= 20 && bossLife > 10)
				{

				}
				else
				{

				}
				if (count == 10)
				{
					count = 0;
					bulletCount++;
				}
			}
		}
		else if (mode == Mode::Hard)
		{
			if (phase == Phase::Phase1)
			{
				if (count == 1)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(1000.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(110) + (i / 10.0f), 12.0f);
								break;
							}
						}
					}
				}
				if (count == 2)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(1000.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(100), 12.0f);
								break;
							}
						}
					}
				}
				if (count == 3)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(1000.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(90) + (i / 50.0f), 12.0f);
								break;
							}
						}
					}
				}
				if (count == 4)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(1000.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(60) + (i / 5.0f), 12.0f);
								break;
							}
						}
					}
				}
				if (count == 5)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(1000.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(70), 12.0f);
								break;
							}
						}
					}
				}
				if (count == 6)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(pos);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(1000.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(-DegreeToRadian(80) - (i / 35.0f), 12.0f);
								break;
							}
						}
					}
				}
				if (count >= 8)
				{
					angle += addAngle1 + (PI / 18);
					count = 0;
				}
			}
			if (phase == Phase::Phase2)
			{

			}
			if (phase == Phase::Phase3)
			{
				if (lastPhase == false)
				{
					count = 1;
					lastPhase = true;
				}
				if (count == 1)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(rotatePos1);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(90), 8.0f);
								break;
							}
						}
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(rotatePos1);
								(*itMissiles)->SetAngle(angle - i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(-90), 8.0f);
								break;
							}
						}
					}
				}
				if (count == 1)
				{
					for (int i = 0; i < 12; i++)
					{
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(rotatePos2);
								(*itMissiles)->SetAngle(angle + i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(true);
								(*itMissiles)->SetIsRightAngle(false);
								(*itMissiles)->SetLeftAddAngle(DegreeToRadian(90), 8.0f);
								break;
							}
						}
						for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
						{
							if ((*itMissiles)->GetIsFire() == false)
							{
								(*itMissiles)->SetPos(rotatePos2);
								(*itMissiles)->SetAngle(angle - i * 0.5233333333333333);
								(*itMissiles)->SetSpeed(700.0f);
								(*itMissiles)->SetIsFire(true);
								(*itMissiles)->SetIsLeftAngle(false);
								(*itMissiles)->SetIsRightAngle(true);
								(*itMissiles)->SetRightAddAngle(DegreeToRadian(-90), 8.0f);
								break;
							}
						}
					}
				}
				if (count >= 12)
				{
					angle += addAngle1 + (PI / 18);
					count = 0;
				}
				if (bossLife > 20)
				{

				}
				else if (bossLife > 10 && bossLife <= 20)
				{

				}
				else
				{

				}

			}
		}
		break;
	case END_NUM:
		break;
	default:
		break;
	}
}
