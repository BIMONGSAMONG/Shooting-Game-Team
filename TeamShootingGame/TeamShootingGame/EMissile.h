#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class EMissile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float angle;
	float pingpongAngle[2];
	int random;
	bool isFire;
	float speed;
	float goalTime;
	bool isPingPong;
	float timer;
	Image* img[2];

	bool isSizeDown;
	bool isSizeUp;
	bool isLeftAngle;
	bool isRightAngle;
	float leftAddAngle;
	float rightAddAngle;
	float disappears;

	bool cSpeed;
	float dTime;
	float toTime;
	float chSpeed;
	float saveSpeed;
	float newAngle;
	float destAngle;
	bool cAngle;
	float dATime;
	float toATime;

	bool isDestAngle;

	bool isReverseAngle;
	bool isReverseAngle2;
	float dIsReversTime;
	float toIsReversTime;
	float dReversTime;
	float toReversTime;
	bool cIsReverse;
	float cIsReverseOffTime;
	float dcIsReverseOffTime;

	int life;
	float toPingPongTime;
	float dPingPongTime;

	bool isLR_PingPong;
	float dLR_PingPongTimer;
	float toLR_PingPongTimer;
	float homingAngleTimer;

	EnemyName randomMissile;
	int randomM;

public:
	HRESULT Init();
	void Release();
	void Update(FPOINT targetPos);
	void Render(HDC hdc, EnemyName name, Mode mode);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }
	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT GetPos() { return pos; }
	int GetSize() { return size; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetAngle(float angle) { this->angle = angle; }
	void SetIsPingPong(bool isPingPong) { this->isPingPong = isPingPong; }
	void SetIsSizeDown(bool isSizeDown) { this->isSizeDown = isSizeDown; }
	void SetIsSizeUp(bool isSizeUp) { this->isSizeUp = isSizeUp; }
	void SetIsSize(int size) { this->size = size; }
	void SetLeftAddAngle(float leftAddAngle, float fDivision);
	void SetRightAddAngle(float rightAddAngle, float fDivision);
	void SetIsLeftAngle(bool isLeftAngle) { this->isLeftAngle = isLeftAngle; }
	void SetIsRightAngle(bool isRightAngle) { this->isRightAngle = isRightAngle; }
	void SetDisappears(float disappears) { this->disappears = disappears; }

	void SetC_Speed(bool cSpeed, float toTime, float chSpeed, float saveSpeed);
	void SetC_Angle(bool cAngle, float dATime, float newAngle);
	void SetIsDestAngle(bool isDestAngle) { this->isDestAngle = isDestAngle; }
	bool GetIsDestAngle() { return this->isDestAngle; }
	bool GetIsLeftAngle() { return this->isLeftAngle; }
	bool GetIsRightAngle() { return this->isRightAngle; }

	void SetRevers(float dIsReversTime, float dReversTime, bool isReverseAngle, bool cIsReverse, float dcIsReverseOffTime);
	void SetLife(int life) { this->life = life; }
	void SetDPingPingTime(float dPingPongTime) { this->dPingPongTime = dPingPongTime; }
	void SetToPingPingTime(float toPingPongTime) { this->toPingPongTime = toPingPongTime; }
	void SetIsLR_PingPong(bool isLR_PingPong) { this->isLR_PingPong = isLR_PingPong; }
	void SetdLR_PingPong(float dLR_PingPongTimer) { this->dLR_PingPongTimer = dLR_PingPongTimer; }

	float GetDestAngle() { return destAngle; }
};

