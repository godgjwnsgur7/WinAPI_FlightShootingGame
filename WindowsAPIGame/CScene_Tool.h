#pragma once
#include "CScene.h"

class CScene_Tool : 
	public CScene
{
public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIndex();

	void SaveTileData();
	void SaveTile(const wstring& _strFilePath);
	
	void LoadTileData();

public:
	CScene_Tool();
	~CScene_Tool();
}; 

