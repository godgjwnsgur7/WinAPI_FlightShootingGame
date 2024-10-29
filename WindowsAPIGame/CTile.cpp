#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(3)
{
	SetScale(Vector2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{

}

void CTile::Update()
{

}

void CTile::Render(HDC _dc)
{
	if (nullptr == m_pTileTex || 0 > m_iImgIdx)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;
	
	UINT iCurrRow = m_iImgIdx / iMaxCol;
	UINT iCurrCol = m_iImgIdx % iMaxCol;
	
	if (iMaxRow <= iCurrRow)
		assert(nullptr);

	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vector2 vScale = GetScale();
	
	BitBlt(_dc
		, vRenderPos.x
		, vRenderPos.y
		, vScale.x
		, vScale.y
		, m_pTileTex->GetDC()
		, iCurrCol * TILE_SIZE
		, iCurrRow * TILE_SIZE
		, SRCCOPY);
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
