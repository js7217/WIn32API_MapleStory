#include "stdafx.h"
#include "Armor.h"
#include "Player.h"
#include "ShopArmor.h"
#include "Equipment.h"
#include "Inventory.h"
#include "ObjMgr.h"

#include "AbstractFactory.h"
CArmor::CArmor()
{
}

CArmor::CArmor(int iOption, float fX, float fY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_iRotate = iOption;
}


CArmor::~CArmor()
{
}

void CArmor::Initialize()
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_iHp = 500;
	m_iGold = 1000;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Maple_Resource/Item/Armor.bmp", L"Armor");
	m_pFrameKey = L"Armor";
	CObj::UpdateRect();
}

int CArmor::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CArmor::LateUpdate()
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
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EQUIP_CLICK);
			if (m_iRotate == 1)	//�κ�
			{
				// ���â������ �̵��� �ʿ��ϴ�.
				CObjMgr::Get_Instance()->AddObject(ObjID::CLOTH, CAbstractFactory<CShopArmor>::Create());
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MaxHp(m_iHp);
				dynamic_cast<CEquipment*>(CObjMgr::Get_Instance()->Get_Equipment())->Set_Equip(this, 2);
				CSoundMgr::Get_Instance()->PlayEffect(L"���Һ�.mp3", CSoundMgr::EQUIP_CLICK);
			}
			else if (m_iRotate == 2) // ���â
			{
				CObjMgr::Get_Instance()->DeleteID(ObjID::CLOTH);
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MaxHp(-m_iHp);
				m_iRotate = 1;
			}
			else if (m_iRotate == -1)	//����
			{
				if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Gold() < m_iGold)
					return;
				else
				{
					dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inventory())->Buy_Equip(this, 2); // 1.����, 2.��
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Gold(m_iGold);
				}
			}
			else if (m_iRotate == 0) // �Ǹ�
			{
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Gold(-(m_iGold * 0.5));
				m_bIsDead = true;
			}
		}
	}
}

void CArmor::Render(HDC hDC)
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
		RGB(255, 255, 255));

	if (m_iRotate == -1)
	{
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, m_tInfo.fX + 40.f, m_tInfo.fY - m_tInfo.fCY / 2, L"���� �� ���� ��Ʋ��Ʈ", lstrlen(L"���� �� ���� ��Ʋ��Ʈ"));
		TextOut(hDC, m_tInfo.fX + 50.f, m_tInfo.fY, L"1000 �޼�", lstrlen(L"1000 �޼�"));
	}
}

void CArmor::Release()
{
}
