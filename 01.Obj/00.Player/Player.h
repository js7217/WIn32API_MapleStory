#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	void KeyCheck(); // �⺻ �÷��̾� Ű
	void LopeKeyCheck(); // ������
	void IsJumping();
	void LopeJumping();
	void IsOffSet();
	void MotionChange();
	void PlayerLock(float fX);		//�� ũ�⸦ ����� ���ϰ� ��.
	void LevelUp();
public:
	int& Get_Gold() { return m_iGold; }
public:
	void Set_Lope(bool IsLope) { m_bIsLope = IsLope; }
	void Set_Gold(int iGold) { m_iGold -= iGold; }
	void Set_HpHeal(int iHeal)
	{
		m_iHp += iHeal;
		if (m_iHp >= m_iMaxHp)
			m_iHp = m_iMaxHp;
	}
	void Set_MpHeal(int iHeal)
	{
		m_iMp += iHeal;
		if (m_iMp >= m_iMaxMp)
			m_iMp = m_iMaxMp;
	}
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool m_bIsJump;
	bool m_bIsLope;
	bool m_bIsColl;		// bool������ ������
	int m_iIsColl;		// int������ ������
	int m_iGold;
	float m_fJumpPower; // v
	float m_fJumpAccel; // t
	float m_fLineLX;
	float m_fLineRX;
	DWORD m_dwOldTime;
};

