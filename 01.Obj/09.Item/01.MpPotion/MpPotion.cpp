#include "stdafx.h"
#include "MpPotion.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Inventory.h"
CMpPotion::CMpPotion()
{
}

CMpPotion::CMpPotion(int iOption, float fX, float fY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_iRotate = iOption; // �ɼ� : �κ� 1, ���� -1, �Ǹ� 0 �� ���� �ɼǰ�. 
}


CMpPotion::~CMpPotion()
{

}

void CMpPotion::Initialize()
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_iHeal = 50;
	m_iGold = 100;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/UI/Portion_MP.bmp", L"Portion_MP");
	m_pFrameKey = L"Portion_MP";
	CObj::UpdateRect();
}

int CMpPotion::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CMpPotion::LateUpdate()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM_CLICK);
			m_tInfo.fX = pt.x;
			m_tInfo.fY = pt.y;
			CSoundMgr::Get_Instance()->PlayEffect(L"������Ŭ��.mp3", CSoundMgr::ITEM_CLICK);
		}
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			if (m_iRotate == 1)	//�κ�
			{
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::POTION);
				if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Mp() == dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MaxMp())
					return;
				CSoundMgr::Get_Instance()->PlayEffect(L"���Ǹ���.mp3", CSoundMgr::POTION);
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MpHeal(m_iHeal);
				m_bIsDead = true;
			}
			else if (m_iRotate == -1)	//����
			{
				if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Gold() < m_iGold)
					return;
				else
				{
					dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inventory())->Buy_Item(this, 2);
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Gold(m_iGold);
				}
			}
			else if (m_iRotate == 0) // �Ǹ�
			{
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Gold(-50);
				m_bIsDead = true;
			}
		}
	}
}

void CMpPotion::Render(HDC hDC)
{
	CObj::UpdateRect();
	if (m_bIsDead)
		return;
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(0, 255, 0));

	if (m_iRotate == -1)
	{
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, m_tInfo.fX + 40.f, m_tInfo.fY - m_tInfo.fCY / 2, L"�Ķ� ����", lstrlen(L"�Ķ� ����"));
		TextOut(hDC, m_tInfo.fX + 50.f, m_tInfo.fY, L"100 �޼�", lstrlen(L"100 �޼�"));
	}
}

void CMpPotion::Release()
{
}
