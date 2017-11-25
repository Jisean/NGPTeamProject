#include "StdAfx.h"
#include "Scene.h"

float	g_fLoadingCnt = 0.f;

CScene::CScene(void)
: m_pObjMgr(CObjMgr::GetInst())
{
}

CScene::~CScene(void)
{
}
