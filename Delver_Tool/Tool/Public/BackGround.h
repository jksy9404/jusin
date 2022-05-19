#pragma once

#include "Tool_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CVIBuffer_Rect;
END

BEGIN(Tool)

class CBackGround final : public CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBackGround(const CBackGround& Prototype);
	virtual ~CBackGround() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT  Render() override;

public:
	void	Render_imgui();

private:

	/*����*/

	/*��*/
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

	/*�ؽ���*/
	CTexture*				m_pTextureCom = nullptr;


private:
	_float3					m_vPosition = _float3(0.f, 0.f, 0.f);

private:
	/* ��ü�� ������ �־���� ������Ʈ���� ���(������ü�� ������)�´�. */
	HRESULT SetUp_Components();


public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphic_Device); /* ������ü�� �����. */
	virtual CGameObject* Clone(void* pArg) override; /* �纻��ü�� ����� �����Ѵ�. */
	virtual void Free() override;

};

END