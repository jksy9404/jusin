#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CGameObject(const CGameObject& Prototype);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT  Render();

protected:
	LPDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END