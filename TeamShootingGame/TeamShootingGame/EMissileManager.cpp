#include "EMissileManager.h"
#include "EMissile.h"

HRESULT EMissileManager::Init()
{
	enemyMissileCount = 100;
	vecMissiles.reserve(enemyMissileCount);
	for (int i = 0; i < enemyMissileCount; i++)
	{
		vecMissiles.push_back(new EMissile());
		vecMissiles[i]->Init();
	}

	angle = 0.0f;
	addAngle = PI / 3;

	fireTime = 0.0f;
	count = 0;

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

void EMissileManager::Update(EnemyName name, FPOINT pos, float destAngle, float fireDelay)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Update();
	}

	fireTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (fireTime >= fireDelay)
	{
		Fire(name, pos, destAngle);
		count++;
		fireTime = 0.0f;
	}
}

void EMissileManager::Render(HDC hdc)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Render(hdc);
	}
}

void EMissileManager::Fire(EnemyName name, FPOINT pos, float destAngle)
{
	//for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	//{
	//	if ((*itMissiles)->GetIsFire() == false)
	//	{
			switch (name)
			{
			case Irritation:
				for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
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
				//if (missileMgr)
				//{
				//	missileMgr->Fire(pos, destAngle, 1300);
				//}
				break;
			case Pressure:
				angle += addAngle - (PI / 4);
				for (int i = 0; i < 6; i++)
				{
					for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
					{
						if ((*itMissiles)->GetIsFire() == false)
						{
							(*itMissiles)->SetPos(pos);
							(*itMissiles)->SetAngle(angle + addAngle * i + (PI / 4));
							(*itMissiles)->SetSpeed(1000.0f);
							(*itMissiles)->SetIsFire(true);
							break;
						}
					}
				}
				
				//if (missileMgr)
				//{
				//	destAngle += addAngle - (PI / 4);
				//	for (int i = 0; i < 6; i++)
				//	{
				//		missileMgr->Fire(pos, destAngle + addAngle * i + (PI / 4), 1000.0f);
				//	}
				//}
				break;
			case Loneliness:
				break;
			case Distress:
				//if (missileMgr)
				//{
				//	for (int i = -1; i <= 1; i++)
				//	{
				//		missileMgr->Fire(pos, destAngle + (i / 6.0f), 1000.0f);
				//	}
				//}
				break;
			case Fear:
				break;
			case Hatred:
				//if (missileMgr)
				//{
				//	if (count == 1)
				//	{
				//		for (int i = -4; i <= 4; i++)
				//		{
				//			if (i <= -2)
				//			{
				//				missileMgr->Fire(pos, destAngle + (i / 40.0f) - 0.25f, 1500.0f);
				//			}
				//			else if (i > -2 && i <= 1)
				//			{
				//				missileMgr->Fire(pos, destAngle + (i / 40.0f), 1500.0f);
				//			}
				//			else if (i > 1)
				//			{
				//				missileMgr->Fire(pos, destAngle + (i / 40.0f) + 0.25f, 1500.0f);
				//			}
				//		}
				//	}
				//	else if (count == 3)
				//	{
				//		for (int i = -6; i < 6; i++)
				//		{
				//			if (i <= -4)
				//			{
				//				missileMgr->Fire(pos, destAngle + (i / 40.0f) - 0.3f, 1500.0f);
				//			}
				//			else if (i > -4 && i <= -1)
				//			{
				//				missileMgr->Fire(pos, destAngle + (i / 40.0f) - 0.1f, 1500.0f);
				//			}
				//			else if (i > -1 && i <= 2)
				//			{
				//				missileMgr->Fire(pos, destAngle + (i / 40.0f) + 0.1f, 1500.0f);
				//			}
				//			else if (i > 2)
				//			{
				//				missileMgr->Fire(pos, destAngle + (i / 40.0f) + 0.3f, 1500.0f);
				//			}
				//		}
				//	}
				//	if (count >= 8)
				//	{
				//		count = 0;;
				//	}
				//}
				break;
			case Guilt:
				break;
			case Confusion:
				//if (missileMgr)
				//{
				//	destAngle = 0;
				//	for (int i = 0; i < 4; i++)
				//	{
				//		missileMgr->Fire(pos, destAngle + addAngle * i, 1000.0f);
				//		missileMgr->SetIsPingPong(true);
				//	}
				//}
				break;
			case Emptiness:
				break;
			case Shame:
				break;
			case Frustration:
				break;
			case Jealousy:
				break;
			case Hoplessness:
				break;
			case Anger:
				break;
			case Anxiety:
				break;
			case Sadness:
				break;
			case Panic:
				break;
			case Despair:
				break;
			case END_NUM:
				break;
			default:
				break;
			}
			
	//	}
	//}
}
