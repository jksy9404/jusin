#pragma once

#include "Base.h"

BEGIN(Engine)

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Reserve_Container(_uint iNumLevels);

	/* ��ü���� ������ �߰��Ѵ�.�� */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pGameObject);

	/* ��ü���� �纻�� �����Ͽ� m_pLayers�� �߰����ش�. */
	HRESULT Clone_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg);

	HRESULT	Clear(_uint iLevelIndex);

public:
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);
	
private:
	map<const _tchar*, class CGameObject*>			m_Prototypes;
	typedef map<const _tchar*, class CGameObject*>	PROTOTYPES;

private:
	/* ���� ������ ���պ��� ��ü���� �����Ѵ�. */
	/* ex: �𵥽����ͷ��̾�. ��水ü���̾�. �����̷��̾�. */
	map<const _tchar*, class CLayer*>*			m_pLayers = nullptr;
	typedef map<const _tchar*, class CLayer*>	LAYERS;

	_uint										m_iNumLevels = 0;

private:
	class CGameObject* Find_Prototype(const _tchar* pPrototypeTag);
	class CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);

public:
	virtual void Free() override;
};

END