#pragma once

#include "GameNode.h"

class Image;
class Player;
class EnemyManager;
class MainScene;
class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;

	Image* backBuffer;
	Image* backGround;
	Image* img;
	Player* player;
	EnemyManager* enemyMng;
	MainScene* mainScene;

	struct MOUSE_DATA  //���콺 �ǽð� ��ǥ // ���콺 Ŭ�� ��ǥ
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	MOUSE_DATA mouseData;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render();				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);


	bool IsInRect(FPOINT pos, MOUSE_DATA mouseData, int size);
	
	MainGame();
	~MainGame();
};
