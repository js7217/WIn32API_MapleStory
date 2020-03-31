#pragma once
#include "Obj.h"
class CBossHpBar :
	public CObj
{
public:
	CBossHpBar();
	virtual ~CBossHpBar();
public:
	void UpdateHpBarRect();
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_fMaxfCX;
	TCHAR* m_pHpBarKey;
	INFO m_tHpBarInfo;
	RECT m_tHpBarRect;
};

