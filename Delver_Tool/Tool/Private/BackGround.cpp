#include "..\Public\BackGround.h"

#include "GameInstance.h"
#include "Texture.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CBackGround::CBackGround(const CBackGround & Prototype)
	: CGameObject(Prototype), m_pVIBufferCom(Prototype.m_pVIBufferCom), m_pTextureCom(Prototype.m_pTextureCom)
{
	Safe_AddRef(m_pVIBufferCom);
	Safe_AddRef(m_pTextureCom);
}

/* 원형객체의 초기화과정을 거친다. */
HRESULT CBackGround::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

/* 사본객체의 추가적인 초기화과정을 거친다. */
HRESULT CBackGround::NativeConstruct(void* pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

void CBackGround::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CBackGround::LateTick(_float fTimeDelta)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//m_vPosition += _float3(0.f, 0.f, 1.f) * 1.0f * fTimeDelta;

	__super::LateTick(fTimeDelta);
	
	pGameInstance->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this);

	Safe_Release(pGameInstance);
}

HRESULT CBackGround::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	_float4x4		WorldMatrix, ViewMatrix, ProjMatrix;

	D3DXMatrixIdentity(&WorldMatrix);
	memcpy(&WorldMatrix.m[3][0], &m_vPosition, sizeof(_float3));	
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	D3DXMatrixLookAtLH(&ViewMatrix, &_float3(0.f, 5.f, -4.0f), &_float3(0.f, 0.f, 0.f), &_float3(0.f, 1.f, 0.f));
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);

	D3DXMatrixPerspectiveFovLH(&ProjMatrix, D3DXToRadian(60.0f), _float(g_iWinSizeX) / g_iWinSizeY, 0.2f, 300.f);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

	m_pTextureCom->Bind_Texture(0);

	m_pVIBufferCom->Render();

	Render_imgui();

	return S_OK;
}

void CBackGround::Render_imgui()
{
	ImGui::Begin("BackGround");
	ImGui::Text("Transform");

	//float vec3f[3] = { m_vPosition.x, m_vPosition.y, m_vPosition.z };
	ImGui::DragFloat3("Position", m_vPosition, 0.1f);
	//memcpy(&m_vPosition, &vec3f, sizeof(_float3));

	ImGui::End();
}

HRESULT CBackGround::SetUp_Components()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	m_pVIBufferCom = (CVIBuffer_Rect*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"));
	if (nullptr == m_pVIBufferCom)
		return E_FAIL;

	m_pTextureCom = (CTexture*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Logo"));
	if (nullptr == m_pVIBufferCom)
		return E_FAIL;
	
	Safe_Release(pGameInstance);

	return S_OK;
}

CGameObject * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround*		pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBackGround::Clone(void* pArg)
{
	CBackGround*		pInstance = new CBackGround(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CBackGround::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);

	Safe_Release(m_pTextureCom);
}
