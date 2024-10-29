#pragma once
// sound 용도 - 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// 코드
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

struct SoundInfo
{
	float bgmVolume;
	float sfxVolume;
};

class CSoundMgr
{
	SINGLE(CSoundMgr);

private:
	LPDIRECTSOUND8	m_pSound;	// 사운드카드 대표 객체
	CSound* m_pBGM;				// 현재 지정된 BGM Sound

	SoundInfo m_tSoundInfo;

public:
	void LoadSoundInfo();
	void SaveSoundInfo();

public:
	int init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);

public:
	void Play_BGM(wstring _bgmName);
	void Play_SFX(wstring _sfxName, float _fVolum = 100.f);

public:
	void SetBGMVolume(float _f);
	void SetSFXVolume(float _f);
	int GetBGMVolume() { return m_tSoundInfo.bgmVolume; }
	int GetSFXVolume() { return m_tSoundInfo.sfxVolume; }
};