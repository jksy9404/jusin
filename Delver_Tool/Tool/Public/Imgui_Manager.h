#pragma once

#include "Tool_Defines.h"
#include "Base.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

BEGIN(Tool)

class CImgui_Manager final : public CBase
{
	DECLARE_SINGLETON(CImgui_Manager)

private:
	CImgui_Manager();
	virtual ~CImgui_Manager() = default;

public:
	HRESULT	NativeConstruct(LPDIRECT3DDEVICE9	pGraphic_Device);
	void	BeginRender();
	void	EndRender();

private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;

public:
	virtual void Free() override;
};

END