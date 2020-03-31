#pragma once

typedef struct tagInfo
{
	float fCX;
	float fCY;
	float fX;
	float fY;
}INFO;


typedef struct tagFrame
{
	int iFrameStart; // x������
	int iFrameEnd;   // x������
	int iFrameScene; // y��ǥ.
	DWORD dwFrameSpeed; // �ݺ� �ӵ�.
	DWORD dwFrameTime; // �󸶸�ŭ ������ ��������.
}FRAME;

typedef struct tagLinePos
{
	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float x, float y)
		: fX(x)
		, fY(y)
	{

	}
	float fX;
	float fY;
}LINEPOS;

typedef struct tagLine
{
	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}
	tagLine(LINEPOS& rLPoint, LINEPOS& rRPoint)
		: tLPoint(rLPoint)
		, tRPoint(rRPoint)
	{}

	LINEPOS tLPoint;
	LINEPOS tRPoint;
}LINE;