#include "MainGame.h"
#include "Image.h"
#include "MainScene.h"
#include "BattleScene.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();

	hdc = GetDC(g_hWnd);


	//////// ���� �̹���

	//ImageManager::GetSingleton()->AddImage(EnemyName::Irritation, "Image/EasyMode/Character/Irrietation.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Pressure, "Image/EasyMode/Character/Pressure.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Loneliness, "Image/EasyMode/Character/Loneliness.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Distress, "Image/EasyMode/Character/Distress.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Fear, "Image/EasyMode/Character/Fear.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Hatred, "Image/EasyMode/Character/Hatred.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Guilt, "Image/EasyMode/Character/Guilt.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Confusion, "Image/EasyMode/Character/Confusion.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Emptiness, "Image/EasyMode/Character/Emptieness.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Shame, "Image/EasyMode/Character/Shame.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Frustration, "Image/EasyMode/Character/Frustration.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Jealousy, "Image/EasyMode/Character/Jealousy.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Hoplessness, "Image/EasyMode/Character/Hopelessness.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Anger, "Image/EasyMode/Character/Anger.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Anxiety, "Image/EasyMode/Character/Anxiety.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Sadness, "Image/EasyMode/Character/Sadness.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Panic, "Image/EasyMode/Character/Panic.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage(EnemyName::Panic, "Image/EasyMode/Character/Panic.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Easy_Boss", "Image/EasyMode/Character/SmallEnamy_sheet.bmp", 208 * 4, 16 * 4, 13, 1, true, RGB(255, 0, 255));


	/////// Ÿ�� �̹���
	ImageManager::GetSingleton()->AddImage("Easy_Tile", "Image/EasyMode/Tile_sheet.bmp", 576 * 3, 64 * 3, 18, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Hard_Tile", "Image/HardMode/Tile_sheet.bmp", 576 * 3, 64 * 3, 18, 2, true, RGB(255, 0, 255));
	
	/////// �÷��̾� �̹���
	ImageManager::GetSingleton()->AddImage("Player_White", "Image/Player.bmp", 4 * 3, 11 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Player_Black", "Image/Player_black.bmp", 4 * 3, 11 * 3, true, RGB(255, 0, 255));

	////// �÷��̾� �Ѿ� �̹���
	ImageManager::GetSingleton()->AddImage("Player_Bullet", "Image/player_bullet.bmp", 3 * 3, 11 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Player_Bullet_Black", "Image/player_bullet_Black.bmp", 3 * 3, 11 * 3, true, RGB(255, 0, 255));

	
	////// ȭ��ǥ �̹���
	ImageManager::GetSingleton()->AddImage("����ȭ��ǥ", "Image/left.bmp", 12 * 3, 24 * 3, 18, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("������ȭ��ǥ", "Image/right.bmp", 12 * 3, 24 * 3, 18, 2, true, RGB(255, 0, 255));
												

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	mainScene = new MainScene();
	mainScene->Init();

	battleScene = new BattleScene();
	battleScene->Init();

	backGround = new Image();
	if (FAILED(backGround->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y)))
	{
		// ����ó��
		MessageBox(g_hWnd, "�� ��Ʈ�� ������ �����߽��ϴ�.", "����", MB_OK);
	}

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{

	backBuffer->Release();
	delete backBuffer;

	mainScene->Release();
	delete mainScene;
	
	battleScene->Release();
	delete battleScene;

	backGround->Release();
	delete backGround;

	TimerManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	if (mainScene->GetEnemyChoice())
	{
		if (battleScene) battleScene->Update();
	}

	if (mainScene) mainScene->Update();

	if (mainScene->GetEnemyChoice() == false)
	{
		if (mainScene->GetMode() == Mode::Easy)  //��������϶���
		{
			if (IsInRect(mainScene->GetEasyPos(), mouseData, mainScene->GetEasySize()))
			{
				mainScene->SetEnemyChoice(true);
				battleScene->SetEnemyName(mainScene->GetEasyTileNum());
				mouseData.clickedPosX = NULL; //Ŭ�� ��ǥ�� Ŭ���� �����Ǿ������� �ʱ�ȭ�ؼ� �ٽ� �ȵ����� ����
				mouseData.clickedPosY = NULL;
			}
		}
		else if (mainScene->GetMode() == Mode::Hard)
		{
			if (IsInRect(mainScene->GetHardPos(), mouseData, mainScene->GetHardSize()))
			{
				mainScene->SetEnemyChoice(true);
				battleScene->SetEnemyName(mainScene->GetHardTileNum());
				mouseData.clickedPosX = NULL; //Ŭ�� ��ǥ�� Ŭ���� �����Ǿ������� �ʱ�ȭ�ؼ� �ٽ� �ȵ����� ����
				mouseData.clickedPosY = NULL;
			}
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		mainScene->SetEnemyChoice(false);
	}

	if (mainScene->GetEnemyChoice() == false)
	{
		if (IsInRect2(mainScene->GetRightPos(), mouseData, 36, 72))
		{
			mainScene->SetMode(Mode::Hard);
			mouseData.clickedPosX = NULL; //Ŭ�� ��ǥ�� Ŭ���� �����Ǿ������� �ʱ�ȭ�ؼ� �ٽ� �ȵ����� ����
			mouseData.clickedPosY = NULL;
		}
		if (IsInRect2(mainScene->GetLeftPos(), mouseData, 36, 72))
		{
			mainScene->SetMode(Mode::Easy);
			mouseData.clickedPosX = NULL; //Ŭ�� ��ǥ�� Ŭ���� �����Ǿ������� �ʱ�ȭ�ؼ� �ٽ� �ȵ����� ����
			mouseData.clickedPosY = NULL;
		}
	}

	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	HDC backDC = backBuffer->GetMemDC();
	backGround->Render(backDC, 0, 0);

	char szText[128] = "";

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(backDC, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(backDC, 10, 30, szText, strlen(szText));

	if (mainScene->GetEnemyChoice() == false)
	{
		if (mainScene) mainScene->Render(backDC);
	}
	if (mainScene->GetEnemyChoice())
	{
		if (battleScene) battleScene->Render(backDC);
	}
	TimerManager::GetSingleton()->Render(backDC);
	backBuffer->Render(hdc, 0, 0);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
		//case WM_TIMER:
		//	if (isInit)
		//	{
		//		this->Update();
		//	}
		//	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}
		break;
	case WM_MOUSEMOVE:
		mouseData.mousePosX = LOWORD(lParam);
		mouseData.mousePosY = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

bool MainGame::IsInRect(FPOINT pos, MOUSE_DATA mouseData , int size) //���콺�� ���ʹ�ư Ŭ���� �ش� ��ǥ �׸�ȿ� �ִ���
{
	if (pos.x - (size / 2)  <= mouseData.clickedPosX && mouseData.clickedPosX <= pos.x + (size / 2)
		&& pos.y - (size / 2) <= mouseData.clickedPosY && mouseData.clickedPosY <= pos.y + (size / 2))
	{
		return true;
	}
	return false;
}

bool MainGame::IsInRect2(FPOINT pos, MOUSE_DATA mouseData, int sizeX, int sizeY) //���콺�� ���ʹ�ư Ŭ���� �ش� ��ǥ �׸�ȿ� �ִ���
{
	if (pos.x <= mouseData.clickedPosX && mouseData.clickedPosX <= pos.x + sizeX
		&& pos.y <= mouseData.clickedPosY && mouseData.clickedPosY <= pos.y + sizeY)
	{
		return true;
	}
	return false;
}

MainGame::MainGame()
{
	isInit = false;
}


MainGame::~MainGame()
{
}
