#pragma once
#include "Obj.h"
class CMainUI :
	public CObj
{
public:
	CMainUI();
	virtual ~CMainUI();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

