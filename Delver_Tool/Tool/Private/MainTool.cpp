#include "..\Public\MainTool.h"

#include "GameInstance.h"
#include "Texture.h"
#include "VIBuffer_Rect.h"

CMainTool::CMainTool()
	: m_pGameInstance(CGameInstance::Get_Instance()),
	m_pImgui_Manager(CImgui_Manager::Get_Instance())
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pImgui_Manager);
}

HRESULT CMainTool::NativeConstruct()
{
	GRAPHICDESC		GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(GRAPHICDESC));

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iWinCX = g_iWinSizeX;
	GraphicDesc.iWinCY = g_iWinSizeY;
	GraphicDesc.isWindowed = true;

	if (FAILED(m_pGameInstance->Initialize_Engine(LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
		return E_FAIL;

	if (FAILED(Ready_RenderState()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component_Static()))
		return E_FAIL;



	return S_OK;
}

void CMainTool::Tick(float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

	m_pGameInstance->Tick_Engine(fTimeDelta);

	m_pImgui_Manager->Tick();
}

HRESULT CMainTool::Render()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	//m_pGameInstance->Render_Begin();

	//m_pGameInstance->Render_Engine();

	//m_pGameInstance->Render_End();

	_float4x4		WorldMatrix, ViewMatrix, ProjMatrix;

	D3DXMatrixIdentity(&WorldMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	D3DXMatrixLookAtLH(&ViewMatrix, &_float3(0.f, 5.f, -4.0f), &_float3(0.f, 0.f, 0.f), &_float3(0.f, 1.f, 0.f));
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);

	D3DXMatrixPerspectiveFovLH(&ProjMatrix, D3DXToRadian(60.0f), _float(g_iWinSizeX) / g_iWinSizeY, 0.2f, 300.f);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

	m_pTextureCom->Bind_Texture(0);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CMainTool::Ready_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 0);


	return S_OK;
}

HRESULT CMainTool::Ready_Prototype_Component_Static()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* Prototype_Component_VIBuffer_Rect */
	if (FAILED(m_pGameInstance->Add_ComponentPrototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		CVIBuffer_Rect::Create(m_pGraphic_Device))))
		return E_FAIL;

	/* Prototype_Component_Texture_Logo */
	if (FAILED(m_pGameInstance->Add_ComponentPrototype(LEVEL_LOGO, L"Prototype_Component_Texture_Logo",
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, L"../Bin/Resources/Monster.bmp", 1))))
		return E_FAIL;

	m_pVIBufferCom = (CVIBuffer_Rect*)m_pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"));
	if (nullptr == m_pVIBufferCom)
		return E_FAIL;

	m_pTextureCom = (CTexture*)m_pGameInstance->Clone_Component(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Logo"));
	if (nullptr == m_pVIBufferCom)
		return E_FAIL;

	return S_OK;
}

CMainTool * CMainTool::Create()
{
	CMainTool*		pInstance = new CMainTool();

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("Failed to Created : CMainApp");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainTool::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);

	Safe_Release(m_pVIBufferCom);

	Safe_Release(m_pGameInstance);

	Safe_Release(m_pGraphic_Device);

	CGameInstance::Release_Engine();

	Safe_Release(m_pImgui_Manager);

	CImgui_Manager::Destroy_Instance();
}
