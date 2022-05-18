#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

extern HWND g_hWnd;

namespace Tool
{
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;


	enum LEVEL { LEVEL_STATIC, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_LOADING, LEVEL_END };
}

using namespace Tool;
