#pragma once
class CScene_Result :
	public CScene
{
	bool	m_bMoveSceneLock;

public:
	void GoToTitleScene();

public:
	virtual void Update();

public:
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Result();
	~CScene_Result();
};

