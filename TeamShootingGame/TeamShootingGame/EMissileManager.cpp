#include "EMissileManager.h"
#include "EMissile.h"

HRESULT EMissileManager::Init()
{
	isShoot = true;
	enemyMissileCount = 200;
	vecMissiles.reserve(enemyMissileCount);
	for (int i = 0; i < enemyMissileCount; i++)
	{
		vecMissiles.push_back(new EMissile());
		vecMissiles[i]->Init();
	}

	angle = 0.0f;
	addAngle = PI / 3;

	fireTime = 0.0f;
	count = 1;
	isPattern = false;
	bulletCount = 0;

	return E_NOTIMPL;
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
			/*for (int i = 0 + bulletCount; i < 1 + bulletCount; i++)
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
			}*/
		}
		break;
	case Pressure:
		if (mode == Mode::Easy)
		{
			angle += addAngle - (PI / 4);
			for (int i = 0 + bulletCount; i < 6 + bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetAngle(angle + addAngle * i + (PI / 4));
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
			//angle += addAngle - (PI / 4);
			//for (int i = 0; i < 6; i++)
			//{
			//	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			//	{
			//		if ((*itMissiles)->GetIsFire() == false)
			//		{
			//			(*itMissiles)->SetPos(pos);
			//			(*itMissiles)->SetAngle(angle + addAngle * i + (PI / 4));
			//			(*itMissiles)->SetSpeed(1000.0f);
			//			(*itMissiles)->SetIsFire(true);
			//			break;
			//		}
			//	}
			//}
		}
		break;
	case Loneliness:
		if (mode == Mode::Easy)
		{

		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Distress:
		if (mode == Mode::Easy)
		{
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
		}
		else if (mode == Mode::Hard)
		{
			//for (int i = -1; i <= 1; i++)
			//{
			//	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			//	{
			//		if ((*itMissiles)->GetIsFire() == false)
			//		{
			//			(*itMissiles)->SetPos(pos);
			//			(*itMissiles)->SetAngle(destAngle + (i / 6.0f));
			//			(*itMissiles)->SetSpeed(1000.0f);
			//			(*itMissiles)->SetIsFire(true);
			//			break;
			//		}
			//	}
			//}
		}
		break;
	case Fear:
		if (mode == Mode::Easy)
		{

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
						else if (i > 6 + bulletCount)
						{
							vecMissiles[i]->SetAngle(destAngle + ((i - 4 - bulletCount) / 40.0f) + 0.25f);
						}
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetIsFire(true);
					}
				}
			}
			else if (count == 3)
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
						vecMissiles[i]->SetSpeed(1500.0f);
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
			//if (count == 1)
			//{
			//	for (int i = -4; i <= 4; i++)
			//	{
			//		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			//		{
			//			if ((*itMissiles)->GetIsFire() == false)
			//			{
			//				(*itMissiles)->SetPos(pos);
			//				if (i <= -2)
			//				{
			//					(*itMissiles)->SetAngle(destAngle + (i / 40.0f) - 0.25f);
			//				}
			//				else if (i > -2 && i <= 1)
			//				{
			//					(*itMissiles)->SetAngle(destAngle + (i / 40.0f));
			//				}
			//				else if (i > 1)
			//				{
			//					(*itMissiles)->SetAngle(destAngle + (i / 40.0f) + 0.25f);
			//				}
			//				(*itMissiles)->SetSpeed(1500.0f);
			//				(*itMissiles)->SetIsFire(true);
			//				break;
			//			}
			//		}
			//	}
			//}
			//else if (count == 3)
			//{
			//	for (int i = -6; i < 6; i++)
			//	{
			//		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			//		{
			//			if ((*itMissiles)->GetIsFire() == false)
			//			{
			//				(*itMissiles)->SetPos(pos);
			//				if (i <= -4)
			//				{
			//					(*itMissiles)->SetAngle(destAngle + (i / 40.0f) - 0.3f);
			//				}
			//				else if (i > -4 && i <= -1)
			//				{
			//					(*itMissiles)->SetAngle(destAngle + (i / 40.0f) - 0.1f);
			//				}
			//				else if (i > -1 && i <= 2)
			//				{
			//					(*itMissiles)->SetAngle(destAngle + (i / 40.0f) + 0.1f);
			//				}
			//				else if (i > 2)
			//				{
			//					(*itMissiles)->SetAngle(destAngle + (i / 40.0f) + 0.3f);
			//				}
			//				(*itMissiles)->SetSpeed(1500.0f);
			//				(*itMissiles)->SetIsFire(true);
			//				break;
			//			}
			//		}
			//	}
			//}
			//if (count >= 8)
			//{
			//	count = 0;
			//}
		}
		break;
	case Guilt:
		if (mode == Mode::Easy)
		{

		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Confusion:
		if (mode == Mode::Easy)
		{
			for (int i = 0 + bulletCount; i < 4 + bulletCount; i++)
			{
				if (vecMissiles[i]->GetIsFire() == false)
				{
					vecMissiles[i]->SetPos(pos);
					vecMissiles[i]->SetAngle(0 + addAngle * (i - bulletCount));
					vecMissiles[i]->SetSpeed(1000.0f);
					vecMissiles[i]->SetIsFire(true);
					vecMissiles[i]->SetIsPingPong(true);
				}
			}
			bulletCount += 4;
			if (bulletCount >=192)
			{
				bulletCount = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			//for (int i = 0; i <= 3; i++)
			//{
			//	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
			//	{
			//		if ((*itMissiles)->GetIsFire() == false)
			//		{
			//			(*itMissiles)->SetPos(pos);
			//			(*itMissiles)->SetAngle(0 + addAngle * i);
			//			(*itMissiles)->SetSpeed(1000.0f);
			//			(*itMissiles)->SetIsFire(true);
			//			(*itMissiles)->SetIsPingPong(true);
			//			break;
			//		}
			//	}
			//}
		}
		break;
	case Emptiness:
		if (mode == Mode::Easy)
		{

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
			//if (count <= 4)
			//{
			//	for (int i = 0 + bulletCount; i <= 2 + bulletCount; i++)
			//	{
			//		if (vecMissiles[i]->GetIsFire() == false)
			//		{
			//			vecMissiles[i]->SetPos(pos);
			//			vecMissiles[i]->SetSpeed(1500.0f);
			//			vecMissiles[i]->SetAngle(PI);
			//			vecMissiles[i]->SetIsFire(true);
			//		}
			//		if (vecMissiles[i]->GetIsFire() == true)
			//		{
			//			if (vecMissiles[i]->GetPos().x <= (WINSIZE_X / 2) - 250.0f)
			//			{
			//				vecMissiles[i]->SetSpeed(1800.0f);
			//				destAngle1 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
			//				if (i == 0 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
			//				}
			//				if (i == 1 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
			//				}
			//				if (i == 2 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(destAngle1 + ((i - 1 - bulletCount) / 6.0f));
			//				}
			//			}
			//		}
			//	}
			//	for (int i = 3 + bulletCount; i <= 5 + bulletCount; i++)
			//	{
			//		if (vecMissiles[i]->GetIsFire() == false)
			//		{
			//			vecMissiles[i]->SetPos(pos);
			//			vecMissiles[i]->SetSpeed(1500.0f);
			//			vecMissiles[i]->SetAngle(2 * PI);
			//			vecMissiles[i]->SetIsFire(true);
			//		}
			//		if (vecMissiles[i]->GetIsFire() == true)
			//		{
			//			if (vecMissiles[i]->GetPos().x >= (WINSIZE_X / 2) + 250.0f)
			//			{
			//				vecMissiles[i]->SetSpeed(1800.0f);
			//				destAngle2 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
			//				if (i == 3 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
			//				}
			//				if (i == 4 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
			//				}
			//				if (i == 5 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(destAngle2 + ((i - 4 - bulletCount) / 6.0f));
			//				}
			//			}
			//		}
			//	}
			//}
			//if (count == 4)
			//{
			//	for (int i = 6 + bulletCount; i <= 11 + bulletCount; i++)
			//	{
			//		if (vecMissiles[i]->GetIsFire() == false)
			//		{
			//			vecMissiles[i]->SetPos(pos);
			//			if (i == 6 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.5f);
			//			}
			//			if (i == 7 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.3f);
			//			}
			//			if (i == 8 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) - 0.1f);
			//			}
			//			if (i == 9 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.1f);
			//			}
			//			if (i == 10 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.3f);
			//			}
			//			if (i == 11 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(destAngle + ((i - 9 - bulletCount) / 40.0f) + 0.5f);
			//			}
			//			vecMissiles[i]->SetSpeed(1600.0f);
			//			vecMissiles[i]->SetIsFire(true);
			//		}
			//	}
			//	bulletCount += 12;
			//}
			//if (bulletCount >= 180)
			//{
			//	bulletCount = 0;
			//}
			//if (count >= 10)
			//{
			//	count = 0;;
			//}
		}
		break;
	case Frustration:
		if (mode == Mode::Easy)
		{

		}
		else if (mode == Mode::Hard)
		{

		}
		break;
	case Jealousy:
		if (mode == Mode::Easy)
		{
			if (count <= 4)
			{
				for (int i = 0 + bulletCount; i < 4 + bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetAngle(PI);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
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
								vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
							}
							if (i == 2 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI + (PI / 4));
							}
							if (i == 3 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
							}
						}
					}
				}
				for (int i = 4 + +bulletCount; i < 8 + +bulletCount; i++)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						vecMissiles[i]->SetSpeed(1500.0f);
						vecMissiles[i]->SetAngle(2 * PI);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
					}
					if (vecMissiles[i]->GetIsFire() == true)
					{
						if (vecMissiles[i]->GetPos().x >= (WINSIZE_X / 2) + 250.0f)
						{
							vecMissiles[i]->SetSpeed(1800.0f);
							destAngle2 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
							if (i == 4 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI / 4);
							}
							if (i == 5 + bulletCount)
							{
								vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
							}
							if (i == 6 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI + (PI / 4));
							}
							if (i == 7 + bulletCount)
							{
								vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
							}
						}
					}
				}

			}
			if (count == 4)
			{
				for (int i = 8 + bulletCount; i < 12 + bulletCount; i += 1)
				{
					if (vecMissiles[i]->GetIsFire() == false)
					{
						vecMissiles[i]->SetPos(pos);
						if (i == 8 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI / 4);
						}
						if (i == 9 + bulletCount)
						{
							vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
						}
						if (i == 10 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI + (PI / 4));
						}
						if (i == 11 + bulletCount)
						{
							vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
						}
						vecMissiles[i]->SetSpeed(1800.0f);
						vecMissiles[i]->SetIsFire(true);
						vecMissiles[i]->SetIsPingPong(true);
					}
				}
				bulletCount += 12;
			}
			if (bulletCount >= 180)
			{
				bulletCount = 0;
			}
			if (count >= 14)
			{
				count = 0;
			}
		}
		else if (mode == Mode::Hard)
		{
			//if (count <= 4)
			//{
			//	for (int i = 0 + bulletCount; i < 4 + bulletCount; i++)
			//	{
			//		if (vecMissiles[i]->GetIsFire() == false)
			//		{
			//			vecMissiles[i]->SetPos(pos);
			//			vecMissiles[i]->SetSpeed(1500.0f);
			//			vecMissiles[i]->SetAngle(PI);
			//			vecMissiles[i]->SetIsFire(true);
			//			vecMissiles[i]->SetIsPingPong(true);
			//		}
			//		if (vecMissiles[i]->GetIsFire() == true)
			//		{
			//			if (vecMissiles[i]->GetPos().x <= (WINSIZE_X / 2) - 250.0f)
			//			{
			//				vecMissiles[i]->SetSpeed(1800.0f);
			//				destAngle1 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
			//				if (i == 0 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(PI / 4);
			//				}
			//				if (i == 1 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
			//				}
			//				if (i == 2 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(PI + (PI / 4));
			//				}
			//				if (i == 3 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
			//				}
			//			}
			//		}
			//	}
			//	for (int i = 4 + +bulletCount; i < 8 + +bulletCount; i++)
			//	{
			//		if (vecMissiles[i]->GetIsFire() == false)
			//		{
			//			vecMissiles[i]->SetPos(pos);
			//			vecMissiles[i]->SetSpeed(1500.0f);
			//			vecMissiles[i]->SetAngle(2 * PI);
			//			vecMissiles[i]->SetIsFire(true);
			//			vecMissiles[i]->SetIsPingPong(true);
			//		}
			//		if (vecMissiles[i]->GetIsFire() == true)
			//		{
			//			if (vecMissiles[i]->GetPos().x >= (WINSIZE_X / 2) + 250.0f)
			//			{
			//				vecMissiles[i]->SetSpeed(1800.0f);
			//				destAngle2 = atan2f(-(targetPos.y - vecMissiles[i]->GetPos().y), (targetPos.x - vecMissiles[i]->GetPos().x));
			//				if (i == 4 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(PI / 4);
			//				}
			//				if (i == 5 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
			//				}
			//				if (i == 6 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(PI + (PI / 4));
			//				}
			//				if (i == 7 + bulletCount)
			//				{
			//					vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
			//				}
			//			}
			//		}
			//	}
			//
			//}
			//if (count == 4)
			//{
			//	for (int i = 8 + bulletCount; i < 12 + bulletCount; i += 1)
			//	{
			//		if (vecMissiles[i]->GetIsFire() == false)
			//		{
			//			vecMissiles[i]->SetPos(pos);
			//			if (i == 8 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(PI / 4);
			//			}
			//			if (i == 9 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle((PI / 2) + (PI / 4));
			//			}
			//			if (i == 10 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(PI + (PI / 4));
			//			}
			//			if (i == 11 + bulletCount)
			//			{
			//				vecMissiles[i]->SetAngle(PI + (PI / 2) + (PI / 4));
			//			}
			//			vecMissiles[i]->SetSpeed(1800.0f);
			//			vecMissiles[i]->SetIsFire(true);
			//			vecMissiles[i]->SetIsPingPong(true);
			//		}
			//	}
			//	bulletCount += 12;
			//}
			//if (bulletCount >= 180)
			//{
			//	bulletCount = 0;
			//}
			//if (count >= 14)
			//{
			//	count = 0;
			//}
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

		}
		else if (mode == Mode::Hard)
		{

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

		}
		else if (mode == Mode::Hard)
		{

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
