#pragma once
#include "Obj.h"
class CRedPotion :
	public CObj
{
public:
	CRedPotion();
	CRedPotion(int iOption, float fX, float fY);
	virtual ~CRedPotion();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	int m_iHeal;
	int m_iGold;
};

