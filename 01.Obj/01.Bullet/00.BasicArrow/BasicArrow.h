#pragma once
#include "Bullet.h"
class CBasicArrow :
	public CBullet
{
public:
	CBasicArrow();
	CBasicArrow(float fX, float fY, int Rotate);
	virtual ~CBasicArrow();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

