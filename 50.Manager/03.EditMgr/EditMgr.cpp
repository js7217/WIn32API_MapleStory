#include "stdafx.h"
#include "EditMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Line.h"
#include "Tile.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
IMPLEMENT_SINGLETON(CEditMgr)
CEditMgr::CEditMgr()
	: m_pLineKey(nullptr)
	, m_pTileKey(nullptr)
	, m_iEditType(0)
{
}


CEditMgr::~CEditMgr()
{
	Release();
}

void CEditMgr::Initialize()
{
	CObjMgr::Get_Instance()->Get_Mouse()->Initialize();
	m_iEditType = '1';
}

void CEditMgr::Update()
{
	CObjMgr::Get_Instance()->Get_Mouse()->Update();
	
	if (CKeyMgr::Get_Instance()->KeyDown('1'))
		m_iEditType = '1';
	if (CKeyMgr::Get_Instance()->KeyDown('2'))
		m_iEditType = '2';

	switch (m_iEditType)
	{
	case '1':
		EditLine();
		break;
	case '2':
		EditTile();
		break;
	default:
		break;
	}

	if (CKeyMgr::Get_Instance()->KeyDown('S'))
	{
		SaveLine();
		SaveTile();
	}
	if (CKeyMgr::Get_Instance()->KeyDown('L'))
	{
		LoadLine(m_pLineKey);
		LoadTile(m_pTileKey);
	}
}

void CEditMgr::LateUpdate()
{
	CObjMgr::Get_Instance()->Get_Mouse()->LateUpdate();
}

void CEditMgr::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Get_Mouse()->UpdateRect();
	CObjMgr::Get_Instance()->Get_Mouse()->Render(hDC);
	for (auto& pLine : m_LineList)
		pLine->Render(hDC);
	for (auto& pTile : m_TileList)
		pTile->Render(hDC);
}

void CEditMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();

	for_each(m_TileList.begin(), m_TileList.end(), Safe_Delete<CObj*>);
	m_TileList.clear();
}

void CEditMgr::SaveLine()
{
	// api���� �����ϴ� ���� ������� ��� �Ұ��̴�. 
	HANDLE hFile = CreateFile(m_pLineKey, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	/*
	1. �������ϴ� ���� �̸�
	2. ���� ���� ���
	3. ������ ���� ��� ����. 0���� �θ� ���� �㰡���� ����.
	4. ������ ���� �Ӽ� ����. NULL �ϰ�� ����Ʈ ����
	5. ������ �������� ���� ������ ������
	CREATE_ALWAYS ������ ������ ���� ����, ������ ���� ����
	6. ������ �Ӽ�����. �� �÷��״� �ƹ��� �Ӽ��� ���� ������ ����.
	7. ������ ���ڴ� ������ NULL �� WIN95/98���� ���� ��¼�� ��¼�� �ϴµ� �������� ..

	*/

	// ���� ���� ���н� INVALID_HANDLE_VALUE ���� ��ȯ�Ѵ�. 
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Fail", L"����â", MB_OK);
		return;
	}
	DWORD dwByte = 0;

	for (auto& pLine : m_LineList)
	{
		WriteFile(hFile, &pLine->Get_Line(), sizeof(LINE), &dwByte, nullptr);
		// ������ 0�� �ƴѰ� ���н� 0�� ���� 
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Save����!", L"����â", MB_OK);
}

void CEditMgr::LoadLine(TCHAR* pEditKey)
{
	HANDLE hFile = CreateFile(pEditKey, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"����!", L"�ε� ����â!", MB_OK);
		return;
	}
	LINE tInfo = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		m_LineList.emplace_back(new CLine(tInfo));
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"����!", L"�ε� ����â!", MB_OK);
}

void CEditMgr::SaveTile()
{
	HANDLE hFile = CreateFile(m_pTileKey, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Fail", L"����â", MB_OK);
		return;
	}
	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;

	for (auto& pTile : m_TileList)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	int result = MessageBox(g_hWnd, L"Save����!", L"����â", MB_OK);
	if (result == IDOK)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
}

void CEditMgr::LoadTile(TCHAR * pEditKey)
{
	HANDLE hFile = CreateFile(pEditKey, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"����!", L"�ε� ����â!", MB_OK);
		return;
	}
	INFO tInfo = {};
	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

		m_TileList.emplace_back(pTile);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"����!", L"�ε� ����â!", MB_OK);
}

void CEditMgr::EditLine()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	float fScorllX = CScrollMgr::Get_ScrollX();
	pt.x -= (LONG)fScorllX;
	float fScorllY = CScrollMgr::Get_ScrollY();
	pt.y -= (LONG)fScorllY;

	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		LINE tStartInfo =
		{
			LINEPOS(float(pt.x), float(pt.y)),
			LINEPOS(float(pt.x), float(pt.y)),
		};
		m_LineList.emplace_back(new CLine(tStartInfo));
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
	{
		m_LineList.back()->Set_RightPos(LINEPOS(float(pt.x), float(pt.y)));
	}
}

void CEditMgr::EditTile()
{
	static int iDrawID = 0;
	static int iOptionID = 0;
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	float fScorllX = CScrollMgr::Get_ScrollX();
	pt.x -= (LONG)fScorllX;
	float fScorllY = CScrollMgr::Get_ScrollY();
	pt.y -= (LONG)fScorllY;

	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		m_TileList.emplace_back(CAbstractFactory<CTile>::Create((float)pt.x, (float)pt.y));
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
	{
		for (auto& pTile : m_TileList)
		{
			if (pt.x >= pTile->Get_Rect().left && pt.x <= pTile->Get_Rect().right &&
				pt.y >= pTile->Get_Rect().top && pt.y <= pTile->Get_Rect().bottom)
			{
				++iDrawID;
				++iOptionID;
				if (iDrawID >= 5)
					iDrawID = 0;
				if (iOptionID >= 5)
					iOptionID = 0;
				dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
				dynamic_cast<CTile*>(pTile)->Set_Option(iOptionID);
			}
		}
	}
}
