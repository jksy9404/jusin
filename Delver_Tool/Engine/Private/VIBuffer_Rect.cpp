#include "..\Public\VIBuffer_Rect.h"

CVIBuffer_Rect::CVIBuffer_Rect(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{

}

CVIBuffer_Rect::CVIBuffer_Rect(const CVIBuffer_Rect & Prototype)
	: CVIBuffer(Prototype)
{

}

HRESULT CVIBuffer_Rect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 6;
	m_iStride = sizeof(VTXTEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 2;

	/* ���� ������ �Ҵ��ϳ�. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	/* �Ҵ�� ������ ���� ä���. */
	/* �Ҵ�� ������ �����ؼ� ���� ����ϱ� ����, �Ҵ�� ������ �ּҸ� ���´�. */
	VTXTEX*			pVertices = nullptr;	

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	
	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexUV = _float2(0.0f, 0.f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexUV = _float2(0.0625f, 0.f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexUV = _float2(0.0625f, 0.125f);

	pVertices[3].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[3].vTexUV = _float2(0.f, 0.f);

	pVertices[4].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[4].vTexUV = _float2(0.0625f, 0.125f);

	pVertices[5].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[5].vTexUV = _float2(0.f, 0.125f);

	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Rect::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CComponent * CVIBuffer_Rect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CComponent*		pInstance = new CVIBuffer_Rect(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CVIBuffer_Rect::Clone(void * pArg)
{
	CVIBuffer_Rect*		pInstance = new CVIBuffer_Rect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX("Failed to Clone : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIBuffer_Rect::Free()
{
	__super::Free();
}
