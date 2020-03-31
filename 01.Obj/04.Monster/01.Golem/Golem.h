#pragma once
#include "Monster.h"
class CGolem :
	public CMonster
{
public:
	CGolem();
	virtual ~CGolem();
public:
	void MonsterWalk();
	void MotionChange();
public:
	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_fJumpAccel;
	int m_iGold;
};

