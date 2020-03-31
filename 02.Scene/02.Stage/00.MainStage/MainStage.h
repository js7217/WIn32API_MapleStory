#pragma once
#include "Scene.h"
class CMainStage :
	public CScene
{
public:
	CMainStage();
	virtual ~CMainStage();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	int m_iMapCX;
	int m_iMapCY;
};

