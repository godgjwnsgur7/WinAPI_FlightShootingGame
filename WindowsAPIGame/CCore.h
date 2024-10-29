#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore);
private:
	HWND m_hWnd; // 핸들
	POINT m_ptResolution; // 해상도
	HDC m_hDC;

	CTexture* m_pMemTex; // 백버퍼 텍스처

	// 자주 사용하는 GUI Obj
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// 폰트 추가
	HFONT	m_font;

	// 메뉴
	HMENU	m_hMenu;

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();
	
private:
	void Clear();
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vector2 _vResolution, bool _bMenu);

public:
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};