#pragma once

#include "Imgui_Manager.h"

BEGIN(Engine)
class CGameInstance;
class CVIBuffer_Rect;
class CTexture;
END

class CMainTool final :public CBase
{
private:
	CMainTool();
	virtual ~CMainTool() = default;


public:
	LPDIRECT3DDEVICE9		Get_GraphicDevice() { return m_pGraphic_Device; }

public:
	HRESULT NativeConstruct();
	void	Tick(float fTimeDelta);
	HRESULT Render();

private:
	CGameInstance*				m_pGameInstance = nullptr;
	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;
	CImgui_Manager*				m_pImgui_Manager = nullptr;


#ifdef _DEBUG
private:
	_uint					m_iNumRender = 0;
	_float					m_fTimeAcc = 0.f;
#endif // _DEBUG

private:
	HRESULT Ready_RenderState();
	HRESULT Ready_Prototype_Component_Static();

	void FileTest();

	void Img_Test();
	bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);

public:
	static CMainTool* Create();
	virtual void Free() override;
};

