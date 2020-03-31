#pragma once
#include "Scene.h"

class CStage2 :
	public CScene
{
public:
	CStage2();
	virtual ~CStage2();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MonsterCreate();
private:
	int m_iMapCX;
	int m_iMapCY;
};

