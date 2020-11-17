#include "MainGame.h"
#include "Image.h"
#include "Player.h"
#include "EnemyManager.h"
#include "MainScene.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();

	hdc = GetDC(g_hWnd);


	//////// 몬스터 이미지

	ImageManager::GetSingleton()->AddImage(EnemyName::Irritation, "Image/EasyMode/Character/Irrietation.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Pressure, "Image/EasyMode/Character/Pressure.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Loneliness, "Image/EasyMode/Character/Loneliness.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Distress, "Image/EasyMode/Character/Distress.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Fear, "Image/EasyMode/Character/Fear.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Hatred, "Image/EasyMode/Character/Hatred.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Guilt, "Image/EasyMode/Character/Guilt.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Confusion, "Image/EasyMode/Character/Confusion.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Emptiness, "Image/EasyMode/Character/Emptieness.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Shame, "Image/EasyMode/Character/Shame.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Frustration, "Image/EasyMode/Character/Frustration.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Jealousy, "Image/EasyMode/Character/Jealousy.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Hoplessness, "Image/EasyMode/Character/Hopelessness.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Anger, "Image/EasyMode/Character/Anger.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Anxiety, "Image/EasyMode/Character/Anxiety.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Sadness, "Image/EasyMode/Character/Sadness.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Panic, "Image/EasyMode/Character/Panic.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Panic, "Image/EasyMode/Character/Panic.bmp", 64 * 3, 32 * 3, 2, 1, true, RGB(255, 0, 255));


	/////// 타일 이미지
	ImageManager::GetSingleton()->AddImage("Easy_Tile", "Image/EasyMode/Tile_sheet.bmp", 576 * 3, 64 * 3, 18, 2, true, RGB(255, 0, 255));
	
	/////// 플레이어 이미지
	ImageManager::GetSingleton()->AddImage("Player_White", "Image/Player.bmp", 4 * 3, 11 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Player_Black", "Image/Player_black.bmp", 4 * 3, 11 * 3, true, RGB(255, 0, 255));

	////// 플레이어 총알 이미지
	ImageManager::GetSingleton()->AddImage("Player_Bullet", "Image/player_bullet.bmp", 3 * 3, 11 * 3, true, RGB(255, 0, 255));
	
												

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	mainScene = new MainScene();
	mainScene->Init();

	player = new Player();
	player->Init();

	enemyMng = new EnemyManager();
	enemyMng->Init();

	backGround = new Image();
	if (FAILED(backGround->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y)))
	{
		// 예외처리
		MessageBox(g_hWnd, "빈 비트맵 생성에 실패했습니다.", "실패", MB_OK);
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

	player->Release();
	delete player;

	enemyMng->Release();
	delete enemyMng;

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
		if (player) player->Update();
		if (enemyMng) enemyMng->Update();
	}

	if (mainScene) mainScene->Update();

	if (mainScene->GetEnemyChoice() == false)
	{
		if (IsInRect(mainScene->GetEasyPos(), mouseData, mainScene->GetEasySize()))
		{
			mainScene->SetEnemyChoice(true);
			enemyMng->SetEnemyName(mainScene->GetEasyTileNum());
			mouseData.clickedPosX = NULL; //클릭 좌표가 클릭시 고정되어있으니 초기화해서 다시 안들어오게 해줌
			mouseData.clickedPosY = NULL;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		mainScene->SetEnemyChoice(false);
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
		if (player) player->Render(backDC);
		if (enemyMng) enemyMng->Render(backDC);
	}

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

bool MainGame::IsInRect(FPOINT pos, MOUSE_DATA mouseData , int size) //마우스가 왼쪽버튼 클릭시 해당 좌표 네모안에 있는지
{
	if (pos.x - (size / 2)  <= mouseData.clickedPosX && mouseData.clickedPosX <= pos.x + (size / 2)
		&& pos.y - (size / 2) <= mouseData.clickedPosY && mouseData.clickedPosY <= pos.y + (size / 2))
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
