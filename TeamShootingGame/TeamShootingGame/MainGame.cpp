#include "MainGame.h"
#include "Image.h"
#include "MainScene.h"
#include "BattleScene.h"
#include "TitleScene.h"
#include "Enemy.h"
HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();

	hdc = GetDC(g_hWnd);


	//////// 몬스터 이미지
	ImageManager::GetSingleton()->AddImage(EnemyName::Anger, "Image/Boss/Anger.bmp", 64 * 4, 64 * 4, 2, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Anxiety, "Image/Boss/Anxiety.bmp", 64 * 4, 64 * 4, 2, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Sadness, "Image/Boss/Sadness.bmp", 64 * 4, 64 * 4, 2, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage(EnemyName::Panic, "Image/Boss/Panic.bmp", 64 * 4, 64 * 4, 2, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Small_Boss", "Image/SmallEnamy_sheet.bmp", 208 * 4, 32 * 4, 13, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Easy_Boss", "Image/Boss/Boss_Easy.bmp", 24 * (float)2.5, 64 * (float)2.5, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Hard_Boss", "Image/Boss/Boss_Hard.bmp", 96 * (float)2.5, 64 * (float)2.5, 4, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Boss_FirstBarrier", "Image/Boss/Boss_FirstBarrier.bmp", 768 * (float)2.5, 128 * (float)2.5, 6, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Boss_SecondBarrier", "Image/Boss/Boss_SecondBarrier.bmp", 64 * (float)2.5, 64 * (float)2.5, true, RGB(255, 0, 255));

	/////// 몬스터 총알 이미지
	ImageManager::GetSingleton()->AddImage("Boss_Bullet", "Image/Boss/bullet_sheet.bmp", 144 * 2, 16 * 2, 18, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Fin_Boss_Bullet", "Image/Boss/Boss_Bullet_sheet.bmp", 56 * 2, 8 * 2, 7, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("보스죽음", "Image/Youdied_B.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("일반죽음", "Image/Youdied_N.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	/////// 타일 이미지
	ImageManager::GetSingleton()->AddImage("Easy_Tile", "Image/EasyMode/Tile_sheet.bmp", 576 * 3, 64 * 3, 18, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Hard_Tile", "Image/HardMode/Tile_sheet.bmp", 576 * 3, 64 * 3, 18, 2, true, RGB(255, 0, 255));

	/////// 플레이어 이미지
	ImageManager::GetSingleton()->AddImage("Player_White", "Image/Player.bmp", 4 * 3, 11 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Player_Black", "Image/Player_black.bmp", 4 * 3, 11 * 3, true, RGB(255, 0, 255));

	////// 플레이어 총알 이미지
	ImageManager::GetSingleton()->AddImage("Player_Bullet", "Image/player_bullet.bmp", 3 * 3, 11 * 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Player_Bullet_Black", "Image/player_bullet_Black.bmp", 3 * 3, 11 * 3, true, RGB(255, 0, 255));


	////// 화살표 이미지
	ImageManager::GetSingleton()->AddImage("왼쪽화살표", "Image/left.bmp", 12 * 3, 24 * 3, 18, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("오른쪽화살표", "Image/right.bmp", 12 * 3, 24 * 3, 18, 2, true, RGB(255, 0, 255));

	////// 타이틀 이미지
	ImageManager::GetSingleton()->AddImage("Z키를 누르세요", "Image/TitleScene.bmp", WINSIZE_X, WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("시작화면", "Image/splash.bmp", WINSIZE_X, WINSIZE_Y);

	///// 시크릿?
	ImageManager::GetSingleton()->AddImage("시크릿", "Image/SecretBuger.bmp", WINSIZE_X, WINSIZE_Y);

	///// 보스 배경화면
	ImageManager::GetSingleton()->AddImage("White", "Image/Background_White.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	///// 레이드 타일
	ImageManager::GetSingleton()->AddImage("레이드", "Image/RaidTile.bmp", 194 * 3, 388 * 3, 1, 2, true, RGB(255, 0, 255));


	srand(time(NULL));

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	mainScene = new MainScene();
	mainScene->Init();

	battleScene = new BattleScene();
	battleScene->Init();

	titleScene = new TitleScene();
	titleScene->Init();

	backGround = new Image();
	if (FAILED(backGround->Init("Image/background.bmp", WINSIZE_X + 40, WINSIZE_Y + 40)))
	{
		// 예외처리
		MessageBox(g_hWnd, "빈 비트맵 생성에 실패했습니다.", "실패", MB_OK);
	}

	FinBossBackGround = ImageManager::GetSingleton()->FindImage("White");

	isInit = true;
	shake = 0;
	sec = 0.0f;
	count = 0;
	shaking = false;
	isShake = false;
	clearTimer = 0;

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

	titleScene->Release();
	delete titleScene;

	backGround->Release();
	delete backGround;

	TimerManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	if (sceneNum == Scene::Title)
	{
		if (titleScene) titleScene->Update();
		if (titleScene->GetGoMain()) sceneNum = Scene::Main;
	}
	if (sceneNum == Scene::Main)
	{
		if (mainScene) mainScene->Update();

		if (mainScene->GetMode() == Mode::Easy)  //이지모드일때만
		{
			if (IsInRect(mainScene->GetEasyPos(), mouseData, mainScene->GetEasySize()))
			{
				mainScene->SetEnemyChoice(true);
				battleScene->SetEnemyName(mainScene->GetEasyTileNum());
				battleScene->SetMode(Mode::Easy);
				cName = mainScene->GetEasyTileNum();
			}
		}
		else if (mainScene->GetMode() == Mode::Hard)
		{
			if (IsInRect(mainScene->GetHardPos(), mouseData, mainScene->GetHardSize()))
			{
				mainScene->SetEnemyChoice(true);
				battleScene->SetEnemyName(mainScene->GetHardTileNum());
				battleScene->SetMode(Mode::Hard);
				cName = mainScene->GetHardTileNum();
			}
		}
		else if (mainScene->GetMode() == Mode::Raid)
		{
			if (IsInRect(mainScene->GetRaidPos(), mouseData, mainScene->GetRaidSize()))
			{
				mainScene->SetEnemyChoice(true);
				battleScene->SetEnemyName(EnemyName::RaidMob);
				battleScene->SetMode(Mode::Raid);
				cName = EnemyName::RaidMob;
				battleScene->SetIsRaid(true);
			}
		}

		if (mainScene->GetEnemyChoice()) sceneNum = Scene::Battle;
	}
	if (sceneNum == Scene::Battle)
	{
		if (battleScene) battleScene->Update();

		if (battleScene->GetIsShake())
		{
			sec += TimerManager::GetSingleton()->GetElapsedTime();
			if (sec >= 0.05)
			{
				sec = 0;
				count++;
				if (count == 1 || count == 3)
				{
					shake = -10;
				}
				if (count == 2 || count == 4)
				{
					shake = 10;
				}
				if (count == 5 || count == 7)
				{
					shake = -5;
				}
				if (count == 6 || count == 8)
				{
					shake = 5;
				}
				if (count >= 9)
				{
					shake = 0;
					count = 0;
					battleScene->SetIsShake(false);
				}
			}
		}

		if (battleScene->GetIsClear() == true)
		{
			clearTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (clearTimer >= 2.0f)
			{
				mainScene->SetEnemyChoice(false);

				battleScene->Release();
				delete battleScene;
				battleScene = new BattleScene();
				battleScene->Init();

				sceneNum = Scene::Main;
				clearTimer = 0;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
		{
			mainScene->SetEnemyChoice(false);

			battleScene->Release();
			delete battleScene;
			battleScene = new BattleScene();
			battleScene->Init();
			
			sceneNum = Scene::Main;
		}
		
		if (battleScene->GetIsShake())
		{
			sec += TimerManager::GetSingleton()->GetElapsedTime();
			if (sec >= 0.05)
			{
				sec = 0;
				count++;
				if (count == 1 || count == 3)
				{
					shake = -10;
				}
				if (count == 2 || count == 4)
				{
					shake = 10;
				}
				if (count == 5 || count == 7)
				{
					shake = -5;
				}
				if (count == 6 || count == 8)
				{
					shake = 5;
				}
				if (count >= 9)
				{
					shake = 0;
					count = 0;
					battleScene->SetIsShake(false);
				}
			}
		}

		if (battleScene->GetIsShaking())
		{
			patternTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (patternTimer >= 0.05)
			{
				patternTimer = 0;
				count++;
				if (count == 1 || count == 3)
				{
					shake = -3;
				}
				if (count == 2 || count == 4)
				{
					shake = 3;
				}
				if (count == 5 || count == 7)
				{
					shake = -1;
				}
				if (count == 6 || count == 8)
				{
					shake = 1;
				}
				if (count >= 9)
				{
					shake = 0;
					count = 0;
					battleScene->SetIsShaking(false);
				}
			}
		}
	}




	if (mainScene->GetEnemyChoice() == false)
	{
		if (IsInRect2(mainScene->GetRightPos(), mouseData, 36, 72)) // 오른쪽 화살표
		{
			if (mainScene->GetMode() == Mode::Easy)
			{
				mainScene->SetMode(Mode::Hard);
				mouseData.clickedPosX = NULL; //클릭 좌표가 클릭시 고정되어있으니 초기화해서 다시 안들어오게 해줌
				mouseData.clickedPosY = NULL;
			}
			else if (mainScene->GetMode() == Mode::Secret)
			{
				mainScene->SetMode(Mode::Easy);
				mouseData.clickedPosX = NULL; //클릭 좌표가 클릭시 고정되어있으니 초기화해서 다시 안들어오게 해줌
				mouseData.clickedPosY = NULL;
			}
			else if (mainScene->GetMode() == Mode::Hard)
			{
				mainScene->SetMode(Mode::Raid);
				mouseData.clickedPosX = NULL;
				mouseData.clickedPosY = NULL;
			}

		}
		if (IsInRect2(mainScene->GetLeftPos(), mouseData, 36, 72))
		{
			if (mainScene->GetMode() == Mode::Hard)
			{
				mainScene->SetMode(Mode::Easy);
				mouseData.clickedPosX = NULL; //클릭 좌표가 클릭시 고정되어있으니 초기화해서 다시 안들어오게 해줌
				mouseData.clickedPosY = NULL;
			}
			else if (mainScene->GetMode() == Mode::Easy)
			{
				mainScene->SetMode(Mode::Secret);
				mouseData.clickedPosX = NULL; //클릭 좌표가 클릭시 고정되어있으니 초기화해서 다시 안들어오게 해줌
				mouseData.clickedPosY = NULL;
			}
			else if (mainScene->GetMode() == Mode::Raid)
			{
				mainScene->SetMode(Mode::Hard);
				mouseData.clickedPosX = NULL;
				mouseData.clickedPosY = NULL;
			}

		}
	}

	if (mainScene->GetEnemyChoice() == true)
	{
		mouseData.clickedPosX = NULL; //클릭 좌표가 클릭시 고정되어있으니 초기화해서 다시 안들어오게 해줌
		mouseData.clickedPosY = NULL;
	}

	if (mainScene->GetMode() == Mode::Easy)  //이지모드일때만
	{
		if (cName != EnemyName::Despair)
		{
			if (battleScene->GetEnemy()->GetLife() == 0)
			{
				mainScene->GetEasyModUI()->SetIsClear(true, cName);
			}
		}
		else if (cName == EnemyName::Despair)
		{
			if (battleScene->GetEnemy()->GetFinBossLife() <= 0)
			{
				mainScene->GetEasyModUI()->SetIsClear(true, cName);
			}
		}
	}
	if (mainScene->GetMode() == Mode::Hard)  //하드모드일때만
	{
		if (cName != EnemyName::Despair)
		{
			if (battleScene->GetEnemy()->GetLife() == 0)
			{
				mainScene->GetHardModeUI()->SetIsClear(true, cName);
			}
		}
		else if (cName == EnemyName::Despair)
		{
			if (battleScene->GetEnemy()->GetFinBossLife() <= 0)
			{
				mainScene->GetHardModeUI()->SetIsClear(true, cName);
			}
		}
	}
	if (mainScene->GetMode() == Mode::Raid)
	{
		// 레이드 깨는 조건
	}


	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	HDC backDC = backBuffer->GetMemDC();
	backGround->Render(backDC, 0, 0);

	if (battleScene->GetEnemy()->GetEnemyName() == EnemyName::Despair)
	{
		FinBossBackGround->Render(backDC, WINSIZE_X / 2, WINSIZE_Y / 2);
	}

	if (sceneNum == Scene::Title)
	{
		if (titleScene) titleScene->Render(backDC);
	}
	if (sceneNum == Scene::Main)
	{
		if (mainScene) mainScene->Render(backDC);
	}
	if (sceneNum == Scene::Battle)
	{
		if (battleScene) battleScene->Render(backDC);
	}

	TimerManager::GetSingleton()->Render(backDC);
	backBuffer->Render(hdc, shake, shake);
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

bool MainGame::IsInRect(FPOINT pos, MOUSE_DATA mouseData, int size) //마우스가 왼쪽버튼 클릭시 해당 좌표 네모안에 있는지
{
	if (pos.x - (size / 2) <= mouseData.clickedPosX && mouseData.clickedPosX <= pos.x + (size / 2)
		&& pos.y - (size / 2) <= mouseData.clickedPosY && mouseData.clickedPosY <= pos.y + (size / 2))
	{
		return true;
	}
	return false;
}

bool MainGame::IsInRect2(FPOINT pos, MOUSE_DATA mouseData, int sizeX, int sizeY) //마우스가 왼쪽버튼 클릭시 해당 좌표 네모안에 있는지
{
	if (pos.x - (sizeX / 2) <= mouseData.clickedPosX && mouseData.clickedPosX <= pos.x + (sizeX / 2)
		&& pos.y - (sizeY / 2) <= mouseData.clickedPosY && mouseData.clickedPosY <= pos.y + (sizeY / 2))
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