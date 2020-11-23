#include "EMissile.h"
#include "Image.h"

HRESULT EMissile::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Boss_Bullet");
	isFire = false;
	pos = { 0,0 };
	size = 16;
	angle = -PI / 2;
	speed = 1500.0f;
	goalTime = 5.0f;
	isPingPong = false;

	isSizeDown = false;
	isSizeUp = false;;
	isLeftAngle = false;
	isRightAngle = false;
	leftAddAngle = 0;
	rightAddAngle = 0;

	disappears = 0;


	cSpeed = false;
	dTime = 0;
	toTime = 0;
	chSpeed = 0;
	saveSpeed = 0;
	newAngle = 0;
	cAngle = false;
	dATime = 0;
	toATime = 0;
	isDestAngle = false;
	isReverseAngle = false;
	isReverseAngle2 = false;;
	dIsReversTime = 0;
	toIsReversTime = 0;
	dReversTime = 0;
	toReversTime = 0;
	cIsReverse = false;
	cIsReverseOffTime = 0;
	dcIsReverseOffTime = 0;
	life = 0;
	toPingPongTime = 0;
	dPingPongTime = 0;
	isLR_PingPong = false;
	dLR_PingPongTimer = 0;
	toLR_PingPongTimer = 0;

	return S_OK;
}

void EMissile::Release()
{
}

void EMissile::Update()
{
	random = rand() % 2;
	if (isFire)
	{
		SetC_Speed(cSpeed, toTime, chSpeed, saveSpeed);
		SetC_Angle(cAngle, toATime, newAngle);
		SetRevers(dIsReversTime, dReversTime, isReverseAngle2, cIsReverse, dcIsReverseOffTime);
		pos.x += cosf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		pos.y -= sinf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;

		if (toPingPongTime >= dPingPongTime)
		{
			if (isPingPong)
			{
				timer += TimerManager::GetSingleton()->GetElapsedTime();
				if (timer <= 8.0f)
				{
					if (pos.x - (size / 2) <= 0)
					{
						pingpongAngle[0] = PI - (PI / 2) - (PI / 4);
						pingpongAngle[1] = PI + (PI / 2) + (PI / 4);
						angle = pingpongAngle[random];
					}
					if (pos.x + (size / 2) >= WINSIZE_X)
					{
						pingpongAngle[0] = 0 - (PI / 2) - (PI / 4);
						pingpongAngle[1] = 0 + (PI / 2) + (PI / 4);
						angle = pingpongAngle[random];
					}
					if (pos.y - (size / 2) <= 0)
					{
						pingpongAngle[0] = 0 - (PI / 4);
						pingpongAngle[1] = PI + (PI / 4);
						angle = pingpongAngle[random];
					}
					if (pos.y + (size / 2) >= WINSIZE_Y)
					{
						pingpongAngle[0] = 0 + (PI / 4);
						pingpongAngle[1] = PI - (PI / 4);
						angle = pingpongAngle[random];
					}
				}
			}
			else if (timer > disappears)
			{
				isFire = false;
				timer = 0;
				toPingPongTime = 0;
			}
		}

		if (isLeftAngle)
		{
			if (isReverseAngle == false)
			{
				angle += leftAddAngle;

				pos.x += (cosf(angle)) * speed * 0.00341400015 / goalTime;
				pos.y -= (sinf(angle)) * speed * 0.00341400015 / goalTime;
			}
			else if (isReverseAngle == true)
			{
				angle += (leftAddAngle *-1);

				pos.x += (cosf(angle)) * speed * 0.00341400015 / goalTime;
				pos.y -= (sinf(angle)) * speed * 0.00341400015 / goalTime;
			}

		}
		if (isRightAngle)
		{
			if (isReverseAngle == false)
			{
				angle += rightAddAngle;

				pos.x += cosf(angle) * speed * 0.00341400015 / goalTime;
				pos.y -= sinf(angle) * speed * 0.00341400015 / goalTime;
			}
			else if (isReverseAngle == true)
			{
				angle += (rightAddAngle * -1);

				pos.x += (cosf(angle)) * speed * 0.00341400015 / goalTime;
				pos.y -= (sinf(angle)) * speed * 0.00341400015 / goalTime;
			}
		}
		if (!isLeftAngle && !isRightAngle)
		{
			pos.x += cosf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
			pos.y -= sinf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		}

		//¿ÞÂÊ ¿À¸¥ÂÊ
		if (isLR_PingPong == true)
		{
			if (pos.x - (size / 2) <= 0 || pos.x + (size / 2) >= WINSIZE_X)
			{
				angle = PI - angle;
			}
			toLR_PingPongTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (toLR_PingPongTimer >= dLR_PingPongTimer)
			{
				isLR_PingPong = false;
				isFire = false;
			}
		}

		if (pos.x <= 0 - 50  || pos.x >= WINSIZE_X + 50|| pos.y <= 0 - 50|| pos.y >= WINSIZE_Y + 50)
		{
			isFire = false;
			isSizeDown = false;
			isSizeUp = false;
			angle = 0.0f;
			speed = saveSpeed;
			isDestAngle = false;
			isLeftAngle = false;
			isRightAngle = false;
			isReverseAngle2 = false;
			this->toIsReversTime = 0.0f;
			this->isReverseAngle = false;
			this->leftAddAngle = 0.0;
			this->rightAddAngle = 0.0;
			this->toReversTime = 0.0f;
			cIsReverse = false;
			cIsReverseOffTime = 0;
			toPingPongTime = 0;
			isLR_PingPong = false;
			toLR_PingPongTimer = 0.0;
		}
		if (pos.x <= 150 || pos.x >= WINSIZE_X - 150 || pos.y <= 50 || pos.y >= WINSIZE_Y - 150)
		{
			if (isSizeDown)
			{
				size = 10;
			}
			if (isSizeUp)
			{
				size = 15;
			}
		}
	}
	else if(isFire==false)
	{
		toLR_PingPongTimer = 0.0f;
	}
}

	


	void EMissile::Render(HDC hdc, EnemyName name, Mode mode)
	{
		if (isFire)
		{
			//Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));
			if (img)
			{
				img->FrameRender(hdc, pos.x, pos.y, name, mode);
			}
		}
	}

	void EMissile::SetLeftAddAngle(float leftAddAngle, float fDivision)
	{
		this->leftAddAngle = DegreeToRadian(leftAddAngle) / fDivision;
	}

	void EMissile::SetRightAddAngle(float rightAddAngle, float fDivision)
	{
		this->rightAddAngle = DegreeToRadian(rightAddAngle) / fDivision;
	}


	void EMissile::SetC_Speed(bool cSpeed, float toTime, float chSpeed, float saveSpeed)
	{
		this->cSpeed = cSpeed;
		this->toTime = toTime;
		this->chSpeed = chSpeed;
		this->saveSpeed = saveSpeed;

		if (this->cSpeed == true)
		{
			this->dTime += TimerManager::GetSingleton()->GetElapsedTime();
			if (this->dTime >= toTime)
			{
				this->speed = chSpeed;
				this->dTime = 0.0f;
				this->cSpeed = false;
			}
		}
	}

	void EMissile::SetC_Angle(bool cAngle, float toATime, float newAngle)
	{
		this->cAngle = cAngle;
		this->toATime = toATime;
		this->newAngle = newAngle;


		if (this->cAngle == true)
		{
			this->dATime += TimerManager::GetSingleton()->GetElapsedTime();
			if (this->dATime >= toATime)
			{
				this->angle = this->newAngle;
				this->isLeftAngle = false;
				this->isRightAngle = false;
				this->cAngle = false;
				this->dATime = 0.0f;
			}
		}
	}

	void EMissile::SetRevers(float dIsReversTime, float dReversTime, bool isReverseAngle, bool cIsReverse, float dcIsReverseOffTime)
	{
		this->dIsReversTime = dIsReversTime;
		this->dReversTime = dReversTime;
		this->toIsReversTime += TimerManager::GetSingleton()->GetElapsedTime();
		this->isReverseAngle2 = isReverseAngle;
		this->cIsReverse = cIsReverse;
		this->dcIsReverseOffTime = dcIsReverseOffTime;
		if (this->toIsReversTime >= this->dIsReversTime)
		{
			this->isReverseAngle = isReverseAngle2;

			if (this->cIsReverse)
			{
				this->toReversTime += TimerManager::GetSingleton()->GetElapsedTime();
				this->cIsReverseOffTime += TimerManager::GetSingleton()->GetElapsedTime();
				if (this->toReversTime >= this->dReversTime)
				{
					if (this->isReverseAngle == true)
					{
						this->isReverseAngle2 = false;
					}
					else if (this->isReverseAngle == false)
					{
						this->isReverseAngle2 = true;
					}
					this->toReversTime = 0.0f;
				}
				if (this->cIsReverseOffTime >= this->dcIsReverseOffTime)
				{
					this->cIsReverse = false;
					cIsReverseOffTime = dcIsReverseOffTime;
				}
			}
		}
	}