#include "pch.h"
#include "CAnimator.h"

CAnimator::CAnimator()
	: m_pCurrAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeat(false)
	, m_fScaleSize(1.f)
{
}

CAnimator::~CAnimator()
{
	SafeDeleteMap(m_mapAnim);
}

void CAnimator::Update()
{
	
}

void CAnimator::FinalUpdate()
{
	if (nullptr != m_pCurrAnim)
	{
		m_pCurrAnim->Update();

		if (m_bRepeat && m_pCurrAnim->IsFinish())
		{
			m_pCurrAnim->SetFrame(0);
		}
	}
}

void CAnimator::Render(HDC _dc)
{
	if (nullptr != m_pCurrAnim)
		m_pCurrAnim->Render(_dc, m_fScaleSize);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2 _vLT
		, Vector2 _vSliceSize, Vector2 _vStep, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim =	FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Load(_strRelativePath);

	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurrAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}
