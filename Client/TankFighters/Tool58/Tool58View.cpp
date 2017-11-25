
// Tool58View.cpp : CTool58View Ŭ������ ����
//

#include "stdafx.h"
#include "Tool58.h"

#include "Tool58Doc.h"
#include "Tool58View.h"
#include "Back.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "MapTool.h"
#include "MyForm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;

// CTool58View

IMPLEMENT_DYNCREATE(CTool58View, CScrollView)

BEGIN_MESSAGE_MAP(CTool58View, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTool58View::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTool58View ����/�Ҹ�

CTool58View::CTool58View()
: m_pDevice(CDevice::GetInst())
, m_pTexture(CTextureMgr::GetInst())
, m_pBack(NULL)
//, m_pSingle(NULL)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTool58View::~CTool58View()
{
	
}

BOOL CTool58View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTool58View �׸���

void CTool58View::OnDraw(CDC* /*pDC*/)
{
	CTool58Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

/*
	if(SUCCEEDED( pDC->Rectangle(100, 100, 200, 200)))
	{
		AfxMessageBox(L"����");
		return;
	}
*/

	D3DXMATRIX		matWorld, matScale, matRotZ, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	matWorld = matScale/* * matRotZ*/ * matTrans;

	//float	fX = m_pSingle->GetTexture()->tImgInfo.Width / 2.f;
	//float	fY = m_pSingle->GetTexture()->tImgInfo.Height / 2.f;
	// 
	// 
	//const TEXINFO* pTexture = m_pTexture->GetTexture(L"CUBE");
	const TEXINFO* pTexture = m_pTexture->GetTexture(L"TILE", L"Tile", 3);
	
	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	m_pDevice->GetDevice()->Clear(0, NULL, 
		D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);

	m_pDevice->Render_Begin();


	m_pBack->Render();

	m_pDevice->Render_End();
	m_pDevice->GetDevice()->Present(NULL, NULL, NULL, NULL);

}


// CTool58View �μ�


void CTool58View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTool58View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTool58View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTool58View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CTool58View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTool58View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTool58View ����

#ifdef _DEBUG
void CTool58View::AssertValid() const
{
	CView::AssertValid();
}

void CTool58View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool58Doc* CTool58View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool58Doc)));
	return (CTool58Doc*)m_pDocument;
}
#endif //_DEBUG


// CTool58View �޽��� ó����

void CTool58View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY));

	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());

	RECT		rcWindow;

	pMainFrm->GetWindowRect(&rcWindow);
	// ��ü �������� ����� ������ �Լ�

	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT	rcMainView;
	GetClientRect(&rcMainView);		// ���� �� â�� ũ�⸦ �����ִ� �Լ�

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(NULL, 
		0, 0, 
		int(WINCX + fRowFrm), 
		int(WINCY + fColFrm),
		SWP_NOZORDER);


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	g_hWnd = m_hWnd;

	if(FAILED(m_pDevice->InitDevice()))
	{
		AfxMessageBox(L"Device Create Failed");
		return;
	}

	if(FAILED(m_pTexture->InsertTexture(L"../Texture/Map/Basement_All.png", L"BASEMENT",TEX_SINGLE)))
	{
		AfxMessageBox(L"Basement Texture Load Failed");
		return;
	}

	if(FAILED(m_pTexture->InsertTexture(L"../Texture/Tile/Tile%d.png", L"TILE", 
		TEX_MULTI, L"Tile", 27)))
	{
		AfxMessageBox(L"Tile Texture Load Failed");
		return;
	}

	m_pBack = new CBack;
	m_pBack->Initialize();
	((CBack*)m_pBack)->SetMainView(this);

	/*m_pSingle = new CSingleTexture;
	m_pSingle->InsertTexture(L"../Texture/Cube.png");*/
}

void CTool58View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

		/*if(m_pSingle)
		::Safe_Delete(m_pSingle);
		*/

	::Safe_Delete(m_pBack);

	m_pTexture->DestroyInst();
	m_pDevice->DestroyInst();
}

void CTool58View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	D3DXVECTOR3	vMouse = D3DXVECTOR3(::GetMouse().x + GetScrollPos(0), 
									 ::GetMouse().y + GetScrollPos(1), 
									 0.f);	// ��ũ�� ���� ����� ����� ��

	CMapTool*	pMapTool = &((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_MapTool;

	if(pMapTool->m_iDrawID < 0 || pMapTool->m_iDrawID > 27)
	{
		((CBack*)m_pBack)->TileChange(vMouse, 0);
	}
	else
	{
		((CBack*)m_pBack)->TileChange(vMouse, pMapTool->m_iDrawID);
	}
	
	Invalidate(FALSE);

	((CMainFrame*)AfxGetMainWnd())->m_pMiniView->Invalidate(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);
}

void CTool58View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnMouseMove(nFlags, point);

	if(GetAsyncKeyState(VK_LBUTTON))
		if(GetAsyncKeyState(VK_SPACE))
		OnLButtonDown(nFlags, point);
}
