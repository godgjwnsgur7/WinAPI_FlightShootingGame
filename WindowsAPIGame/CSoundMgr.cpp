#include "pch.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#include "CSound.h" 

#include "CCore.h"
#include "CPathMgr.h"

CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{

}

void LoadSounds()
{
	CResMgr::GetInst()->LoadSound(L"InGameBgm", L"sound\\InGameBgm.wav");
	CResMgr::GetInst()->LoadSound(L"ResultBgm", L"sound\\ResultBgm.wav");
	CResMgr::GetInst()->LoadSound(L"TitleBgm", L"sound\\TitleBgm.wav");

	CResMgr::GetInst()->LoadSound(L"Boom", L"sound\\Boom.wav");
	CResMgr::GetInst()->LoadSound(L"NextLevel", L"sound\\NextLevel.wav");
	CResMgr::GetInst()->LoadSound(L"GameOver", L"sound\\GameOver.wav");
	CResMgr::GetInst()->LoadSound(L"Shoot", L"sound\\Shoot.wav");
	CResMgr::GetInst()->LoadSound(L"ItemPickUp", L"sound\\ItemPickUp.wav");
	CResMgr::GetInst()->LoadSound(L"Boss", L"sound\\Boss.wav");
	CResMgr::GetInst()->LoadSound(L"Death", L"sound\\Death.wav");
	CResMgr::GetInst()->LoadSound(L"Destroy", L"sound\\Destroy.wav");

	CResMgr::GetInst()->LoadSound(L"UI_Click_Cancel", L"sound\\UI_Click_Cancel.wav");
	CResMgr::GetInst()->LoadSound(L"UI_Click_Enter", L"sound\\UI_Click_Enter.wav");
	CResMgr::GetInst()->LoadSound(L"UI_GameStartInfo", L"sound\\UI_GameStartInfo.wav");
	CResMgr::GetInst()->LoadSound(L"UI_Result", L"sound\\UI_Result.wav");
	CResMgr::GetInst()->LoadSound(L"UI_Click_Error", L"sound\\UI_Click_Error.wav");
}

void CSoundMgr::LoadSoundInfo()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"sound\\SoundInfo.text";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	string str;
	char szBuff[256] = {};
	FScanf(szBuff, pFile);
	m_tSoundInfo.bgmVolume = std::stoi(szBuff);
	FScanf(szBuff, pFile);
	m_tSoundInfo.sfxVolume = std::stoi(szBuff);

	fclose(pFile);
}

void CSoundMgr::SaveSoundInfo()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"sound\\SoundInfo.text";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	fprintf(pFile, std::to_string((int)m_tSoundInfo.bgmVolume).c_str());
	fprintf(pFile, "\n");
	fprintf(pFile, std::to_string((int)m_tSoundInfo.sfxVolume).c_str());
	fprintf(pFile, "\n");
	
	fclose(pFile);
}

int CSoundMgr::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 디바이스 협조레벨 설정.
	HWND hWnd = CCore::GetInst()->GetMainHwnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag값 정리
	{
		MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	LoadSounds();
	LoadSoundInfo();
	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}

void CSoundMgr::Play_BGM(wstring _bgmName)
{
	CSound* pNewSound = CResMgr::GetInst()->FindSound(_bgmName);
	pNewSound->SetPosition(50.f);
	pNewSound->PlayToBGM(true);
}

void CSoundMgr::Play_SFX(wstring _sfxName, float _fVolum)
{
	CSound* pNewSound = CResMgr::GetInst()->FindSound(_sfxName);
  	pNewSound->SetVolume(m_tSoundInfo.sfxVolume * (_fVolum / 100));
	pNewSound->SetPosition(50.f);
	pNewSound->Play(false);
}

void CSoundMgr::SetBGMVolume(float _f)
{
	m_tSoundInfo.bgmVolume = _f;
	m_pBGM->SetVolume(_f);
	SaveSoundInfo();
}

void CSoundMgr::SetSFXVolume(float _f)
{
	m_tSoundInfo.sfxVolume = _f;
	SaveSoundInfo();
}
