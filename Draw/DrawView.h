
// DrawView.h : CDrawView ��Ľӿ�
//

#pragma once

class CDrawView : public CView
{

protected: // �������л�����
	
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// ����
public:
	CDrawDoc* GetDocument() const;

	

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int PushNumb; //������¼�����������Ĵ���
	int m_DrawCurrent;//������¼���ڵĲ������
	CPoint m_bO; // Բ��
	CPoint m_bR; //Բ�ϵĵ�
	int m_ist; //Բ����Բ���ϵ������m_ist=0����ʾ��������ΪԲ�ģ�
			   //m_ist=1����ʾ��������ΪԲ���ϵĵ�
	CPoint m_rO;
	CPoint m_rR;
	int mR_ist;
	bool curveFlag;

	COLORREF m_color;  //ȫ����ɫ
	int penStyle;   //������
	int penWidth;   //�߿�

	int m_iPolyDotNumbers;//����ζ������(�ߵĸ���)

	CPoint m_ptPolyDotArrays[999];//�洢����εĶ���

	struct myFont  //������Ϣ�ṹ��
	{
		CFont newFont;
		CFont* oldFont;
		CString text;
		int size;
		CString faceName;
	}m_font;
private:
	CPoint mPointOrign, mPointOld;
	

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPline();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void drawCircle(CClientDC* pDC, CPoint cenp, CPoint ardp);
	int computeRadius(CPoint cenp, CPoint ardp);
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawRectangle();
	void testCircle(CDC* pDC, CPoint cenp, CPoint ardp);
	void drawRect(CClientDC* ht, CPoint cPoint, CPoint ePoint);
	afx_msg void OnInsertText();
	void drawText(CClientDC* ht,CPoint curPoint, CString text);
	afx_msg void OnColorBlack();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnColorCustom();
	afx_msg void OnPenstyleSolid();
	afx_msg void OnPanstyleDash();
	afx_msg void OnPanstyleDot();
	afx_msg void OnPanstyleDashdot();
	afx_msg void OnPanstyleDashdotdot();
	afx_msg void OnPenwidthThin();
	afx_msg void OnPenwidthMid();
	afx_msg void OnPenwidthThick();
	afx_msg void OnPenwidthCustom();
	afx_msg void OnDrawPolygon();
	afx_msg void OnEraseAll();
	afx_msg void OnEraseCustom();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void drawCurve(CClientDC* ht, CPoint first, CPoint second);
	afx_msg void OnDrawCustom();
};

#ifndef _DEBUG  // DrawView.cpp �еĵ��԰汾
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }

#endif



