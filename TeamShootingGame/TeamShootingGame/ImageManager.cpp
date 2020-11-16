#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
}

void ImageManager::AddImage(int strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 맵에 키에 해당하는 데이터가 있는지 확인해서
	// 있으면 추가 없이 리턴
	if (FindImage(strKey))
	{
		return;
	}

	// 없으면 추가
	Image* image = new Image();
	if (FAILED(image->Init(fileName, width, height, isTrans, transColor)))
	{
		image->Release();
		delete image;

		return;
	}

	mapImageDatas.insert(make_pair(strKey, image));
}

void ImageManager::AddImage(int strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (FindImage(strKey))
	{
		return;
	}

	Image* image = new Image();
	if (FAILED(image->Init(fileName, width, height,
		maxFrameX, maxFrameY, isTrans, transColor)))
	{
		image->Release();
		delete image;

		return;
	}

	mapImageDatas.insert(make_pair(strKey, image));
}

void ImageManager::DeleteImage(int strKey)
{
	map<int, Image*>::iterator it = mapImageDatas.find(strKey);
	if (it != mapImageDatas.end())
	{
		(it->second)->Release();
		delete (it->second);

		mapImageDatas.erase(it);
	}
}

Image* ImageManager::FindImage(int strKey)
{
	map<int, Image*>::iterator it = mapImageDatas.find(strKey);
	if (it != mapImageDatas.end())
	{
		return it->second;
	}

	return nullptr;
}
