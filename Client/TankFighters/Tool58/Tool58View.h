
// Tool58View.h : CTool58View Ŭ������ �������̽�
//


#pragma once

#include "SingleTexture.h"

class CDevice;
class CTextureMgr;
class CObj;
class CTool58Doc;
class CTool58View : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CTool58View();
	DECLARE_DYNCREATE(CTool58View)

// Ư���Դϴ�.
public:
	CTool58Doc* GetDocument() const;

// �۾��Դϴ�.
public:
	CDevice*		m_pDevice;
	CTextureMgr*	m_pTexture;
	//CSingleTexture*	m_pSingle;
	CObj*			m_pBack;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTool58View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Tool58View.cpp�� ����� ����
inline CTool58Doc* CTool58View::GetDocument() const
   { return reinterpret_cast<CTool58Doc*>(m_pDocument); }
#endif

