#pragma once
#include "CUI.h"
#include "CScene.h"

typedef void(CScene::* SCENE_MEMFUNC)(void);

class CTextUI;

class CBtnUI :
	public CUI
{
private:
	SCENE_MEMFUNC	m_pSceneFunc;
	CScene*			m_pSceneInst;
	CTextUI*		m_pTextUI;

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
	{
		m_pSceneInst = _pScene;
		m_pSceneFunc = _pSceneFunc;
	}

	CLONE(CBtnUI);
public:
	CBtnUI();
	CBtnUI(wstring _textStr, int _iTextSize);
	~CBtnUI();
};
