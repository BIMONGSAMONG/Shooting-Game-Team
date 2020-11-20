#pragma once

#include "GameNode.h"

class Image;
class Player;
class EnemyManager;
class MainScene;
class BattleScene;
class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;

	Image* backBuffer;
	Image* backGround;
	Image* img;
	MainScene* mainScene;
	BattleScene* battleScene;
	EnemyName cName;

	struct MOUSE_DATA  //���콺 �ǽð� ��ǥ // ���콺 Ŭ�� ��ǥ
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	MOUSE_DATA mouseData;

	int shake;
	float sec;
	int count;
	bool shaking;

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