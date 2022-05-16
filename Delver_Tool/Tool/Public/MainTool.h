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


	/*¸ðµ¨*/
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

	/*ÅØ½ºÃÄ*/
	CTexture*				m_pTextureCom = nullptr;

private:
	HRESULT Ready_RenderState();
	HRESULT Ready_Prototype_Component_Static();

public:
	static CMainTool* Create();
	virtual void Free() override;
};

