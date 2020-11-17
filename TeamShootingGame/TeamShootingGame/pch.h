#pragma once

#include <Windows.h>
#include <math.h>
#include <string>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"

#define WINSIZE_X	1025
#define WINSIZE_Y	770
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)




#define MOUSE_LBUTTON 0x01	// 마우스 왼쪽버튼

#define KEY_Z		0x5A	// 총알 쏘는 키
#define KEY_R		0x82	// 리스타트
#define KEY_Q		0x81	// 메인으로 나가기

#define KEY_UP		0x26
#define KEY_DOWN	0x28
#define KEY_LEFT	0x25
#define KEY_RIGHT	0x27



struct FPOINT
{
	float x;
	float y;
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;


enum Scene {  // 씬 종류
	Title,
	Main,
	Battle
};

enum Mode {  // 모드 종류
	Easy,
	Hard
};

enum EnemyName { // 적 종류
	Irritation,
	Pressure,
	Loneliness,
	Distress,
	Fear,
	Hatred,
	Guilt,
	Confusion,
	Emptiness,
	Shame,
	Frustration,
	Jealousy,
	Hoplessness,
	Anger,
	Anxiety,
	Sadness,
	Panic,
	Despair,
	END_NUM
};

