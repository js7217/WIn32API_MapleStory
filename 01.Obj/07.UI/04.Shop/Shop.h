#pragma once
#include "Obj.h"
class CShop :
	public CObj
{
public:
	CShop();
	virtual ~CShop();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	vector<CObj*> m_VectorShop;
	float m_fItemX;
	float m_fItemY;
	float m_fDistanceY;
};

