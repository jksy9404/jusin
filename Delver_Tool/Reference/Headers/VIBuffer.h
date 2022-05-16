#pragma once

#include "Component.h"

BEGIN(Engine)

/* ���� Ư�� ���� ���� ������ ������ �����Ҵ��Ͽ� �����Ѵ�. */
class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual HRESULT Render();

protected:
	/* ���� ���۸� ��ǥ�ϴ� �İ�ü.*/
	LPDIRECT3DVERTEXBUFFER9				m_pVB = nullptr;
	_uint								m_iNumVertices = 0; /* ������ ���� */
	_uint								m_iStride = 0; /* �����ϳ��� byteũ��. */
	_ulong								m_dwFVF = 0;
	D3DPRIMITIVETYPE					m_ePrimitiveType;
	_uint								m_iNumPrimitive = 0;

protected:
	HRESULT Create_VertexBuffer();

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();
};

END