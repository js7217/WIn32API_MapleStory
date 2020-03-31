#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"
#include "Player.h"
#include "ObjMgr.h"
IMPLEMENT_SINGLETON(CLineMgr)

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::LineCollision(float fInX, float fInY, float * pOutY, float * pOutLineLX, float * pOutLineRX)
{		// 1,2 : ��ü x,y��ǥ, 3 : �浹�� ����� y��ǥ, 4,5 : ������ ó���� ������.(x��ǥ)
	if (m_LineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& pLine : m_LineList)
	{
		float inclination = pLine->Get_inclination();	//a����
		float x = pLine->Get_Line().tLPoint.fX;
		float y = pLine->Get_Line().tLPoint.fY;
		float LineY = inclination * (fInX - x) + y;	//ax + b = y ������ y��ǥ��.

		if (fInY <= LineY)	// �÷��̾� y ���̶� ���� y���̶� ��
		{
			if (fInX >= pLine->Get_Line().tLPoint.fX && fInX <= pLine->Get_Line().tRPoint.fX)
			{
				pTarget = pLine;
			}
		}
	}
	if (nullptr == pTarget)
		return false;
	// ������ ������ ���.
	// y = m(x - x1) + y1;
	// y = (y2 - y1) / (x2 - x1) *(x - x1) + y1; // x,y�� �÷��̾� ��ǥ.
	// x1,y1 : Left
	// x2,y2 : Right
	float x1 = pTarget->Get_Line().tLPoint.fX;
	float y1 = pTarget->Get_Line().tLPoint.fY;
	float x2 = pTarget->Get_Line().tRPoint.fX;
	float y2 = pTarget->Get_Line().tRPoint.fY;
	*pOutY = (y2 - y1) / (x2 - x1) * (fInX - x1) + y1;
	*pOutLineLX = pTarget->Get_Line().tLPoint.fX;
	*pOutLineRX = pTarget->Get_Line().tRPoint.fX;
	return true;
}

void CLineMgr::LoadData(TCHAR* pSaveKey)
{
	HANDLE hFile = CreateFile(pSaveKey, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
	//	MessageBox(g_hWnd, L"����!", L"�ε� ����â!", MB_OK);
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
	//MessageBox(g_hWnd, L"����!", L"�ε� ����â!", MB_OK);
}

void CLineMgr::Initialize()
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_LineList)
		pLine->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}
