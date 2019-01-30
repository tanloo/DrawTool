
// DrawView.h : CDrawView 类的接口
//

#pragma once

class CDrawView : public CView
{

protected: // 仅从序列化创建
	
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// 特性
public:
	CDrawDoc* GetDocument() const;

	

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int PushNumb; //用来记录按下鼠标左键的次数
	int m_DrawCurrent;//用来记录现在的操作类别
	CPoint m_bO; // 圆心
	CPoint m_bR; //圆上的点
	int m_ist; //圆心与圆周上点的区别，m_ist=0，表示鼠标左击点为圆心，
			   //m_ist=1，表示鼠标左击点为圆周上的点
	CPoint m_rO;
	CPoint m_rR;
	int mR_ist;
	bool curveFlag;

	COLORREF m_color;  //全局颜色
	int penStyle;   //笔线性
	int penWidth;   //线宽

	int m_iPolyDotNumbers;//多边形顶点个数(边的个数)

	CPoint m_ptPolyDotArrays[999];//存储多边形的顶点

	struct myFont  //字体信息结构体
	{
		CFont newFont;
		CFont* oldFont;
		CString text;
		int size;
		CString faceName;
	}m_font;
private:
	CPoint mPointOrign, mPointOld;
	

// 生成的消息映射函数
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

#ifndef _DEBUG  // DrawView.cpp 中的调试版本
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }

#endif



