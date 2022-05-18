
// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>

#include "MainTool.h"

// Data
HWND						g_hWnd;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	// Create application window
	//ImGui_ImplWin32_EnableDpiAwareness();
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
	::RegisterClassEx(&wc);
	//HWND
	g_hWnd = ::CreateWindow(wc.lpszClassName, _T("Delver Tool"), WS_OVERLAPPEDWINDOW, 0, 0, g_iWinSizeX, g_iWinSizeY, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	CMainTool*	pMainTool = CMainTool::Create();
	if (nullptr == pMainTool)
	{
		Safe_Release(pMainTool);
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	::ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(g_hWnd);

	// Main loop
	bool done = false;
	while (!done)
	{
		// Poll and handle messages (inputs, window resize, etc.)
		// See the WndProc() function below for our to dispatch events to the Win32 backend.
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				done = true;
		}
		if (done)
			break;

		pMainTool->Tick(0.f);
		pMainTool->Render();

	}

	Safe_Release(pMainTool);
	::DestroyWindow(g_hWnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}

// Helper functions

//bool CreateDeviceD3D(HWND hWnd)
//{
//	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
//		return false;
//
//	// Create the D3DDevice
//	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
//	g_d3dpp.Windowed = TRUE;
//	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
//	g_d3dpp.EnableAutoDepthStencil = TRUE;
//	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
//	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
//	
//	// g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
//	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
//		return false;
//
//	return true;
//}
//
//void CleanupDeviceD3D()
//{
//	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
//	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
//}
//
//void ResetDevice()
//{
//	ImGui_ImplDX9_InvalidateDeviceObjects();
//	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
//	if (hr == D3DERR_INVALIDCALL)
//		IM_ASSERT(0);
//	ImGui_ImplDX9_CreateDeviceObjects();
//}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		/*if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}*/
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_DPICHANGED:
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
		{
			//const int dpi = HIWORD(wParam);
			//printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
			const RECT* suggested_rect = (RECT*)lParam;
			::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
