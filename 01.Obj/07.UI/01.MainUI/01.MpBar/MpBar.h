#pragma once
#include "Obj.h"
class CMpBar :
	public CObj
{
public:
	CMpBar();
	virtual ~CMpBar();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_iDamageUI;
	float m_fMaxfCX;
};

