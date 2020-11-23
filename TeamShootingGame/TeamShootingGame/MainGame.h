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

	struct MOUSE_DATA  //���콺 �ǽð� ��ǥ // ���콺 Ŭ�� ��ǥ
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
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render();				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);


	bool IsInRect(FPOINT pos, MOUSE_DATA mouseData, int size);
	bool IsInRect2(FPOINT pos, MOUSE_DATA mouseData, int sizeX, int sizeY);
	MainGame();
	~MainGame();
};