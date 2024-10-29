#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	CScene* m_pCurrScene;
	SCENE_TYPE m_eNextScene;

	float	m_fCurrTime;
	bool	m_bSceneChange;

	const float FADETIME = 1.f;
	
public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	CScene* GetCurrScene() { return m_pCurrScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};

