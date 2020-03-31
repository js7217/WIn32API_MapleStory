#pragma once
#include "Obj.h"
class CPortal :
	public CObj
{
public:
	CPortal();
	CPortal(float fX, float fY);
	virtual ~CPortal();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

