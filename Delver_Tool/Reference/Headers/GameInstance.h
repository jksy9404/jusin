#pragma once

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Timer_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Renderer.h"

/* Ŭ���̾�Ʈ�� ���� ��������� �Լ��� ��Ƴ��´�. */
/* ��Ŭ���̾�Ʈ ���忡���� ������ ����� ��������� GameIsntance�� �����ϸ�ȴ�. */

BEGIN(Engine)
class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance);
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.GameInstance */
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut); /* ������ ����� ����ϱ����� �ʱ�ȭ�� �ʿ��� �༮���� �ʱ�ȭ�Ѵ�. */
	void Tick_Engine(_float fTimeDelta); /* �������Ӹ��� ������ �ʿ��� �Ŵ������� ����. */
	HRESULT Render_Engine();

public: /* For.Graphic_Device */	
	void Render_Begin();
	void Render_End();

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pNextLevel);

public: /* For.Timer_Manager */
	_float Get_TimeDelta(const _tchar* pTimerTag);
	HRESULT Add_Timer(const _tchar* pTimerTag);
	void Update_Timer(const _tchar* pTimerTag);

public: /*For.Object_Manager */
	HRESULT Add_ObjectPrototype(const _tchar* pPrototypeTag, class CGameObject* pGameObject);	
	HRESULT Clone_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* For.Component_Manager */
	HRESULT Add_ComponentPrototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* For.Renderer */
	HRESULT Add_RenderGroup(CRenderer::RENDERGROUP eRenderGroup, class CGameObject* pGameObject);


private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CTimer_Manager*					m_pTimer_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CRenderer*						m_pRenderer = nullptr;

public:
	static void Release_Engine(); /* �������� ���� ���� �Ŵ����� �޸� ����. */

public:
	virtual void Free() override;
};

END