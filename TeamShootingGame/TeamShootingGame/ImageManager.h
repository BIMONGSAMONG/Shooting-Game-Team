#pragma once
#include "pch.h"
#include "Singleton.h"
#include <map>

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<int, Image*> mapImageDatas;
	map<string, Image*> mapImageDatas_string;

public:
	HRESULT Init();
	void Release();

	void AddImage(int strKey, const char* fileName, int width, int height,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	void AddImage(int strKey, const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	void DeleteImage(int strKey);
	Image* FindImage(int strKey);

	void AddImage(string strKey, const char* fileName, int width, int height,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	void AddImage(string strKey, const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = FALSE, COLORREF transColor = FALSE);

	void DeleteImage(string strKey);
	Image* FindImage(string strKey);
};

