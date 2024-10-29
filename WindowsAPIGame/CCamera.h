#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	NONE,
	FADE_IN,
	FADE_OUT,
};

struct tCamEffect
{
	CAM_EFFECT	eEffect;
	float		fDuration;
	float		fCurrTime;
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vector2		m_vLookAt;
	Vector2		m_vCurrLookAt;
	Vector2		m_vPrevLookAt;

	CObject*	m_pTargetObj;
	Vector2		m_vDiff;

	float		m_fTime; 
	float		m_fSpeed;
	float		m_fAccTime;

	list<tCamEffect>	m_listCamEffect;
	CTexture*			m_pVeilTex;

	bool		m_bFadeEffectState;

public:
	void SetLookAt(Vector2 vLook)
	{
		m_vLookAt = vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetCurrLookAt(Vector2 vLook) { m_vLookAt = vLook; }
	void SetTarget(CObject* _pTargetObj) { m_pTargetObj = _pTargetObj; }
	
	Vector2 GetLookAt() { return m_vCurrLookAt; }
	Vector2 GetRenderPos(Vector2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vector2 GetRealPos(Vector2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	bool GetFadeEffectState() { return m_bFadeEffectState; }

	void FadeIn(float _fDuration)
	{
		m_bFadeEffectState = true;
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurrTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}
	void FadeOut(float _fDuration)
	{
		m_bFadeEffectState = true;
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurrTime = 0.f;
		
		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}

public:
	void Init();
	void Update();
	void Render(HDC _dc);

private:
	void CalDiff();
};

