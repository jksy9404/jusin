#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

/* ���� Ŭ���� .*/
/* ���۷��� ī��Ʈ�� �����Ѵ�*/
class ENGINE_DLL CBase abstract
{
protected:	
	CBase();
	virtual ~CBase() = default;

public:
	unsigned long AddRef(); /* ���� ������ ������Ų��, ������Ų ���۷���ī��Ʈ�� �����Ѵ�. */
	unsigned long Release(); /* ���ҽ�Ų��. or �����Ѵ�. ���ҽ�Ű�� ������ ���۷��� ī��Ʈ�� �����Ѵ�. */

private:
	/* ���� ������ ��� �����Ѵ�. */
	unsigned long		m_dwRefCnt = 0;

public:
	virtual void Free();

};

END



