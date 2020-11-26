#include "UI.h"
#include "Image.h"

HRESULT UI::Init()
{
	ImageManager::GetSingleton()->AddImage("»Úªˆ", "Image/lifebar_white.bmp", WINSIZE_X, 8 * 3.20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("ª°∞≠", "Image/lifebar_red.bmp", WINSIZE_X - 10, 6 * 3.22, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("∞À¡§", "Image/lifebar_black.bmp", WINSIZE_X - 10, 6 * 3.22, true, RGB(255, 0, 255));

	lifeBar[LifebarColor::White] = ImageManager::GetSingleton()->FindImage("»Úªˆ");
	lifeBar[LifebarColor::Red] = ImageManager::GetSingleton()->FindImage("ª°∞≠");
	lifeBar[LifebarColor::Black] = ImageManager::GetSingleton()->FindImage("∞À¡§");

	red = WINSIZE_X - 10;
	black = WINSIZE_X - 10;
	whiteBar = WINSIZE_X - 10;

	sec = 0.0f;

	fRed = 5;
	fBlack = 5;

	oneCheck = false;

	return S_OK;
}

void UI::Release()
{
}

void UI::Update(int life, int bossLife, int firstBarrierLife, int secondBarrierLife, EnemyName name, Phase phase, int raidLife, bool isRaid)
{
	if (isRaid == false)
	{
		if (name <= EnemyName::Panic)
		{
			if (life != FULL_LIFE)
			{
				black = ((WINSIZE_X - 10) / FULL_LIFE) * life;
			}

			sec += TimerManager::GetSingleton()->GetElapsedTime();

			if (sec >= 0.05)
			{
				if (red > black)
				{
					red -= 8.0f;
				}
				sec = 0.0f;
			}
		}

		if (name == EnemyName::Despair)
		{
			sec += TimerManager::GetSingleton()->GetElapsedTime();
			if (phase == Phase::Phase1)
			{
				if (firstBarrierLife != FULL_LIFE)
				{
					black = ((WINSIZE_X - 10) / FULL_LIFE) * firstBarrierLife;
				}
				if (sec >= 0.05)
				{
					if (red > black)
					{
						red -= 8.0f;
					}
					sec = 0.0f;
				}
			}
			if (phase == Phase::Phase2)
			{
				if (secondBarrierLife == FULL_LIFE)
				{
					fRed = WINSIZE_X - 5;  red = 0;
					fBlack = WINSIZE_X - 5;  black = 0;
				}
				else
				{
					fBlack = (WINSIZE_X - 5) - (((WINSIZE_X - 5) / FULL_LIFE) * (FULL_LIFE - secondBarrierLife));
					black = ((WINSIZE_X - 5) / FULL_LIFE) * (FULL_LIFE - secondBarrierLife);
				}
				if (sec >= 0.05)
				{
					if (fRed > fBlack)
					{
						fRed -= 10.0f;
						red += 10.0f;
					}
					sec = 0.0f;
				}
			}
			if (phase == Phase::Phase3)
			{
				if (bossLife == FULL_LIFE)
				{
					red = WINSIZE_X - 10;

				}
				else
				{
					red = ((WINSIZE_X - 5) / FULL_LIFE) * bossLife;
				}
			}
		}
	}
	else
	{

		if (raidLife != RAID_MAX_LIFE)
		{
			black = ((WINSIZE_X - 10) / RAID_MAX_LIFE) * raidLife;
		}
		sec += TimerManager::GetSingleton()->GetElapsedTime();

		if (sec >= 0.05)
		{
			if (red > black)
			{
				red -= 4.0f;
			}
			sec = 0.0f;
		}
	}
}

	void UI::Render(HDC hdc, EnemyName name, Phase phase, Mode mode , bool isRaid)
	{
		if (isRaid == false)
		{
			if (name <= EnemyName::Panic)
			{
				lifeBar[LifebarColor::White]->Render(hdc, 0, 0, White);
				lifeBar[LifebarColor::Red]->Render(hdc, 5, 2.5, Red, red);
				lifeBar[LifebarColor::Black]->Render(hdc, 5, 2.5, Black, black);
			}
			if (name == EnemyName::Despair)
			{
				if (phase == Phase::Phase1)
				{
					lifeBar[LifebarColor::White]->Render(hdc, 0, 0, White);
					lifeBar[LifebarColor::Red]->Render(hdc, 5, 2.5, Red, red);
					lifeBar[LifebarColor::Black]->Render(hdc, 5, 2.5, Black, black);
				}
				if (phase == Phase::Phase2)
				{
					lifeBar[LifebarColor::White]->Render(hdc, 0, 0, White);
					lifeBar[LifebarColor::Black]->Render(hdc, fBlack, 2.5, Black, black);
					lifeBar[LifebarColor::Red]->Render(hdc, fRed, 2.5, Red, red);
				}
				if (phase == Phase::Phase3)
				{
					lifeBar[LifebarColor::White]->Render(hdc, 0, 0, White);
					lifeBar[LifebarColor::Red]->Render(hdc, 5, 2.5, Red, red);
				}
			}

			AddFontResource("Font/Piacevoli.ttf");

			HFONT hFont = CreateFont(45, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, TEXT("Piacevoli"));
			HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

			if (name == EnemyName::Irritation)
			{
				wsprintf(szText, "Irritation");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(200, 231, 0));
				}
				else
				{
					SetTextColor(hdc, RGB(31, 0, 231));
				}

			}
			if (name == EnemyName::Pressure)
			{
				wsprintf(szText, "Pressure");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(216, 63, 0));
				}
				else
				{
					SetTextColor(hdc, RGB(0, 153, 216));
				}

			}
			if (name == EnemyName::Loneliness)
			{
				wsprintf(szText, "Loneliness");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(122, 113, 234));
				}
				else
				{
					SetTextColor(hdc, RGB(225, 234, 113));
				}

			}
			if (name == EnemyName::Distress)
			{
				wsprintf(szText, "Distress");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(255, 213, 1));
				}
				else
				{
					SetTextColor(hdc, RGB(1, 43, 255));
				}

			}
			if (name == EnemyName::Fear)
			{
				wsprintf(szText, "Fear");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(132, 132, 132));
				}
				else
				{
					SetTextColor(hdc, RGB(51, 51, 51));
				}

			}
			if (name == EnemyName::Hatred)
			{
				wsprintf(szText, "Hatred");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(141, 0, 0));
				}
				else
				{
					SetTextColor(hdc, RGB(0, 141, 141));
				}

			}
			if (name == EnemyName::Guilt)
			{
				wsprintf(szText, "Guilt");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(126, 83, 210));
				}
				else
				{
					SetTextColor(hdc, RGB(167, 210, 83));
				}

			}
			if (name == EnemyName::Confusion)
			{
				wsprintf(szText, "Confusion");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(204, 121, 29));
				}
				else
				{
					SetTextColor(hdc, RGB(29, 112, 204));
				}

			}
			if (name == EnemyName::Emptiness)
			{
				wsprintf(szText, "Emptiness");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(51, 51, 51));
				}
				else
				{
					SetTextColor(hdc, RGB(69, 69, 69));
				}

			}
			if (name == EnemyName::Shame)
			{
				wsprintf(szText, "Shame");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(222, 50, 98));
				}
				else
				{
					SetTextColor(hdc, RGB(50, 222, 174));
				}

			}
			if (name == EnemyName::Frustration)
			{
				wsprintf(szText, "Frustration");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(54, 65, 138));
				}
				else
				{
					SetTextColor(hdc, RGB(138, 127, 54));
				}

			}
			if (name == EnemyName::Jealousy)
			{
				wsprintf(szText, "Jealousy");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(236, 240, 81));
				}
				else
				{
					SetTextColor(hdc, RGB(85, 81, 240));
				}

			}
			if (name == EnemyName::Hoplessness)
			{
				wsprintf(szText, "Hoplessness");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(78, 64, 96));
				}
				else
				{
					SetTextColor(hdc, RGB(82, 96, 64));
				}

			}
			if (name == EnemyName::Anger)
			{
				wsprintf(szText, "Anger");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(234, 26, 0));
				}
				else
				{
					SetTextColor(hdc, RGB(0, 208, 234));
				}

			}
			if (name == EnemyName::Anxiety)
			{
				wsprintf(szText, "Anxiety");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(234, 26, 0));
				}
				else
				{
					SetTextColor(hdc, RGB(0, 208, 234));
				}

			}
			if (name == EnemyName::Sadness)
			{
				wsprintf(szText, "Sadness");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(42, 48, 60));
				}
				else
				{
					SetTextColor(hdc, RGB(60, 54, 42));
				}

			}
			if (name == EnemyName::Panic)
			{
				wsprintf(szText, "Panic");
				if (mode == Mode::Easy)
				{
					SetTextColor(hdc, RGB(42, 48, 60));
				}
				else
				{
					SetTextColor(hdc, RGB(60, 54, 42));
				}

			}
			if (name == EnemyName::Despair)
			{
				wsprintf(szText, "Despair");
				SetTextColor(hdc, RGB(0, 0, 0));
			}


			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, 10, 8 * 3.20, szText, strlen(szText));


			SelectObject(hdc, oldFont);
			DeleteObject(hFont);
		}
		else
		{
		lifeBar[LifebarColor::White]->Render(hdc, 0, 0, White);
		lifeBar[LifebarColor::Red]->Render(hdc, 5, 2.5, Red, red);
		lifeBar[LifebarColor::Black]->Render(hdc, 5, 2.5, Black, black);
		 }
}
