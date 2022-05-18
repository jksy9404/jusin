#pragma once

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include "Imgui_Manager.h"
class CExample
{
public:
	CExample();
	~CExample();

public:
	HRESULT NativeConstruct(LPDIRECT3DDEVICE9 pGraphic_Device);
	void Render();
	void CreateSpapes();
	void CreateImg();
	void CreateImageButton();
	bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);

private:
	bool Circlefov = false;
	bool Rectfov = false;
	bool showing = true;
	float Circlesize = 0;
	float Rectsize = 0;

	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;


	int my_image_width = 0;
	int my_image_height = 0;
	LPDIRECT3DTEXTURE9 my_texture = NULL;
	LPDIRECT3DTEXTURE9 texture = NULL;
	int imageButtonClick_Count = 0;
};

