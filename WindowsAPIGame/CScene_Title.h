#pragma once
#include "CScene.h"

class CSettingPopupUI;

class CScene_Title :
	public CScene
{
	CSettingPopupUI*	m_pSettingPopupUI;
	
	bool	m_bGameStartLock;

public:
	void GoToGameScene();
	void ExitGame();
	
public:
	void OpenSettingPopupUI();
	void CloseSettingPopupUI();

public:
	virtual void Update();

public:
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Title();
	~CScene_Title();
};

