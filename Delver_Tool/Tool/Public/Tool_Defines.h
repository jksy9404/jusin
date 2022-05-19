#pragma once


#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "ImGuiFileDialog.h"

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

extern HWND g_hWnd;

namespace Tool
{
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;


	enum LEVEL { LEVEL_STATIC, LEVEL_END };
}

using namespace Tool;
