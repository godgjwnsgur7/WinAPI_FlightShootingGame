#pragma once

#include "CAnimation.h"

class CObject;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;
	CAnimation*	m_pCurrAnim;
	CObject*	m_pOwner;

	float		m_fScaleSize;
	bool		m_bRepeat;

public:
	CObject* GetObj() { return m_pOwner; }
	bool IsFinishAnim() 
	{
		if (m_pCurrAnim == nullptr)
			return false;

		return m_pCurrAnim->IsFinish(); 
	}
	wstring GetCurrAnimName() { return m_pCurrAnim->GetName(); }

public:
	void SetScaleSize(float _fScaleSize) { m_fScaleSize = _fScaleSize; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2 _vLT
		, Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount);
	void LoadAnimation(const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);
	 
	void Update();
	void FinalUpdate();
	void Render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

