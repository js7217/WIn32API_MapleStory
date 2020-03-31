#pragma once
#include "Obj.h"
class CMonster :	// IDLE, HIT, JUMP, WALK_LEFT, WAL_RIGHT, DIE
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();
public:
	void Set_Line(float fLineLX, float fLineRY) { m_fLineLX = fLineLX; m_fLineRX = fLineRY; }
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
protected:
	bool m_bHit;
	float m_fLineLX;			// �浹�� ������ ���� x��ǥ
	float m_fLineRX;			// �浹�� ������ ������ x��ǥ 
};

