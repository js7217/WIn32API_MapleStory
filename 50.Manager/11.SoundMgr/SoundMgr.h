#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)
private:
	CSoundMgr();
	~CSoundMgr();
public:
	enum CHANNELID { BGM, PLAYER_JUMP, PLAYER_SHOOT, PLAYER_HIT,
		SKILL_FIRE, SKILL_TORNADO, POTION, ITEM_GET, ITEM_CLICK, ITEM_UP, INVENTORY, 
		MONSTER_HIT, MONSTER_DEAD, EFFECT, UI, SHOP, POTAL, EQUIP_CLICK, 
		MOUSE_COLLISION, MOUSE_CLICK, MAXCHANNEL };

	void Initialize();
	void Update();
	void Release();

public:
	void PlayEffect(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eId);
	void AllStop();
private:
	void LoadSoundFile();
private:
	// FMOD_SOUND ���� ���ҽ� ������ ���� ��ü .
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	//FMOD_CHANNEL ����ϰ� �ִ� ���带 ������ ��ü  
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];

	// ���� ä�� ��ü �� ��ġ�� �����ϴ� ��ü. 
	FMOD_SYSTEM* m_pSystem;
};

