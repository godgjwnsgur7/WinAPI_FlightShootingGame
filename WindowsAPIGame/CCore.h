#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore);
private:
	HWND m_hWnd; // �ڵ�
	POINT m_ptResolution; // �ػ�
	HDC m_hDC;

	CTexture* m_pMemTex; // ����� �ؽ�ó

	// ���� ����ϴ� GUI Obj
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// ��Ʈ �߰�
	HFONT	m_font;

	// �޴�
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