#pragma once

#include "GameNode.h"

class Image;
class Player;
class EnemyManager;
class MainScene;
class BattleScene;
class TitleScene;
class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;

	Scene sceneNum;

	Image* backBuffer;
	Image* backGround;
	Image* img;
	MainScene* mainScene;
	BattleScene* battleScene;
	TitleScene* titleScene;
	EnemyName cName;

	struct MOUSE_DATA  //마우스 실시간 좌표 // 마우스 클릭 좌표
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	MOUSE_DATA mouseData;

	int shake;
	float sec;
	float patternTimer;
	int count;
	bool shaking;
	bool isShake;

public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render();				// 프레임 단위 출력 (이미지, 텍스트 등)

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);


	bool IsInRect(FPOINT pos, MOUSE_DATA mouseData, int size);
	bool IsInRect2(FPOINT pos, MOUSE_DATA mouseData, int sizeX, int sizeY);
	MainGame();
	~MainGame();
};