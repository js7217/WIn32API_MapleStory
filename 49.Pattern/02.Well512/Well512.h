#pragma once
class CWell512
{
public:
	CWell512();
	~CWell512();
public:
	unsigned int GetValue();
	unsigned int GetValue(unsigned int nMinValue, unsigned int nMaxValue); // ����
	float GetFloatValue();
	float GetFloatValue(float fMinValue, float fMaxValue); // �Ǽ�
private:
	unsigned long state[16];
	unsigned int index;
};

