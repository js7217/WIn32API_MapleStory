#pragma once
#include "Obj.h"
class CObj;
class CShopNpc :
	public CObj
{
public:
	CShopNpc();
	virtual ~CShopNpc();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	vector<CObj*> m_VectorShop;
};

