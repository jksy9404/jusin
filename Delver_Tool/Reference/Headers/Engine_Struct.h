#pragma once

namespace Engine
{
	typedef struct tagGraphicDesc
	{
		HWND hWnd;
		unsigned int iWinCX;
		unsigned int iWinCY;
		bool isWindowed;
	}GRAPHICDESC;

	// D3DDECLUSAGE
	typedef struct tagVertex_Texture
	{
		D3DXVECTOR3		vPosition; /* ��ġ. */
		D3DXVECTOR2		vTexUV; /* �ؽ��� ��ǥ. */	

	}VTXTEX;



	

}