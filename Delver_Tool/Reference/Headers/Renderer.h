#pragma once

/* ȭ�鿡 �׷��� ��ü���� �׷����� ���������� ��Ƴ��´�.  */
/* */

#include "Base.h"

BEGIN(Engine)

class CRenderer final : public CBase
{
	DECLARE_SINGLETON(CRenderer)

public:
	enum RENDERGROUP { RENDER_PRIORITY, RENDER_NONALPHABLEND, RENDER_ALPHABLEND, RENDER_UI, RENDER_END };
public:
	CRenderer();
	virtual ~CRenderer() = default;

public:
	HRESULT Add_RenderGroup(RENDERGROUP eRenderGroup, class CGameObject* pGameObject);
	HRESULT Draw_RenderGroup();


private:
	list<class CGameObject*>			m_RenderList[RENDER_END];
	typedef list<class CGameObject*>	RENDERLIST;	

public:
	virtual void Free() override;
};

END