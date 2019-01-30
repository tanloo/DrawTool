
// DrawView.cpp : CDrawView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Draw.h"

#endif

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"
#include "TextDlg.h"
#include "FontWidthCustom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define NULLMODE 0
#define LINEMODE 1
#define PLINEMODE 2
#define CIRCLEMODE 3
#define RECTMODE 4
#define TEXTMODE 5
#define POLYGONMODE 6
#define ERASEMODE 7
#define CURVEMODE 8

#define COLOR_BLACK RGB(0,0,0)
#define COLOR_RED RGB(255,0,0)
#define COLOR_GREEN RGB(0,255,0)
#define COLOR_BLUE RGB(0,0,255)

#define PEN_WIDTH_THIN 1
#define PEN_WIDTH_MID 3
#define PEN_WIDTH_THICK 7

// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	//ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_COMMAND(ID_DRAW_LINE, &CDrawView::OnDrawLine)
	ON_COMMAND(ID_DRAW_PLINE, &CDrawView::OnDrawPline)

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_CIRCLE, &CDrawView::OnDrawCircle)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CDrawView::OnDrawRectangle)
	ON_COMMAND(ID_INSERT_TEXT, &CDrawView::OnInsertText)
	ON_COMMAND(ID_COLOR_BLACK, &CDrawView::OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, &CDrawView::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CDrawView::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CDrawView::OnColorBlue)
	ON_COMMAND(ID_COLOR_CUSTOM, &CDrawView::OnColorCustom)
	ON_COMMAND(ID_PENSTYLE_SOLID, &CDrawView::OnPenstyleSolid)
	ON_COMMAND(ID_PANSTYLE_DASH, &CDrawView::OnPanstyleDash)
	ON_COMMAND(ID_PANSTYLE_DOT, &CDrawView::OnPanstyleDot)
	ON_COMMAND(ID_PANSTYLE_DASHDOT, &CDrawView::OnPanstyleDashdot)
	ON_COMMAND(ID_PANSTYLE_DASHDOTDOT, &CDrawView::OnPanstyleDashdotdot)
	ON_COMMAND(ID_PENWIDTH_THIN, &CDrawView::OnPenwidthThin)
	ON_COMMAND(ID_PENWIDTH_MID, &CDrawView::OnPenwidthMid)
	ON_COMMAND(ID_PENWIDTH_THICK, &CDrawView::OnPenwidthThick)
	ON_COMMAND(ID_PENWIDTH_CUSTOM, &CDrawView::OnPenwidthCustom)
	ON_COMMAND(ID_DRAW_POLYGON, &CDrawView::OnDrawPolygon)
	ON_COMMAND(ID_ERASE_ALL, &CDrawView::OnEraseAll)
	ON_COMMAND(ID_ERASE_CUSTOM, &CDrawView::OnEraseCustom)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_DRAW_CUSTOM, &CDrawView::OnDrawCustom)
END_MESSAGE_MAP()

// CDrawView 构造/析构
CDrawView::CDrawView()
{
	// TODO: 在此处添加构造代码
	m_bO.x = 0; m_bO.y = 0;
	m_bR.x = 0; m_bR.y = 0;
	PushNumb = 0;
	m_ist = 0;
	mR_ist = 0;
	m_color = COLOR_BLACK;
	penStyle = PS_SOLID;
	penWidth = 1;
	m_iPolyDotNumbers = 0;
	curveFlag = FALSE;
}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	
	return CView::PreCreateWindow(cs);
}

// CDrawView 绘制

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//pDC->SelectStockObject(NULL_BRUSH);
	//testCircle(pDC, m_bO, m_bR);
}


// CDrawView 打印


void CDrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

//void CDrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CDrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	//#ifndef SHARED_HANDLERS
	//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	//#endif
}


// CDrawView 诊断

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView 消息处理程序


void CDrawView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()
}


void CDrawView::OnDrawLine()
{
	PushNumb = 0;
	m_DrawCurrent = LINEMODE;
}


void CDrawView::OnDrawPline()
{
	PushNumb = 0;
	m_DrawCurrent = PLINEMODE;
}

void CDrawDoc::SetTitle(LPCTSTR lpszTitle)

{
	CDocument::SetTitle(L"唐禄棕");
}


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CClientDC ht(this);
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CPen cPen;
	cPen.CreatePen(penStyle, penWidth, m_color);
	CPen *pOldPen = ht.SelectObject(&cPen);

	switch (m_DrawCurrent)
	{
	case LINEMODE:
		if (PushNumb == 0) {
			pMain->AddStrOutputDebugWnd(_T("开始绘制单线段"));
			PushNumb++;
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("（%ld ，%ld）"), point.x, point.y);
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(pointStr);
			SetCapture();
		}
		else if (PushNumb == 1) {
			ht.MoveTo(mPointOrign);
			ht.LineTo(point);
			PushNumb = 0;
			CString pointInfo, mPointOrignStr, mPointOldStr;
			mPointOrignStr.Format(_T("（%ld ，%ld）"), mPointOrign.x, mPointOrign.y);
			mPointOldStr.Format(_T("（%ld ，%ld）"), mPointOld.x, mPointOld.y);
			pointInfo = _T("所画线的坐标从") + mPointOrignStr + "到" + mPointOldStr;
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(mPointOldStr);
			pMain->AddStrOutputDebugWnd(pointInfo);
			ReleaseCapture();
		}
		break;
	case PLINEMODE:
		if (PushNumb == 0) {
			pMain->AddStrOutputDebugWnd(_T("开始绘制多线段"));
			PushNumb++;
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("（%ld ，%ld）"), point.x, point.y);
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(pointStr);
			SetCapture();
		}
		else {
			ht.MoveTo(mPointOrign);
			ht.LineTo(point);
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("（%ld ，%ld）"), point.x, point.y);
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(pointStr);
		}
		break;
	case CIRCLEMODE:
		ht.SelectStockObject(NULL_BRUSH);
		if (!m_ist) {
			m_bO = m_bR = point;
			m_ist++;
		}
		else {
			m_bR = point;
			m_ist--;
			drawCircle(&ht, m_bO, m_bR);
			UpdateData(TRUE);
			CString circleInfo;
			circleInfo.Format(_T("圆绘制结束，圆心为（%ld，%ld），半径为 %d"), m_bO.x, m_bO.y, computeRadius(m_bO, m_bR));
			pMain->AddStrOutputDebugWnd(circleInfo);
			ReleaseCapture();
		}
		break;

	case RECTMODE:
		ht.SelectStockObject(NULL_BRUSH);
		if (!mR_ist) {
			m_rO = m_rR = point;
			mR_ist++;
		}
		else {
			m_rR = point;
			mR_ist--;
			drawRect(&ht, m_rO, m_rR);
			UpdateData(TRUE);
			CString rectInfo;
			rectInfo.Format(_T("矩形绘制结束，中心点为（%ld，%ld），边长为 %d"), m_rO.x, m_rO.y, computeRadius(m_rO, m_rR) * 2);
			pMain->AddStrOutputDebugWnd(rectInfo);
			ReleaseCapture();
		}
		break;

	case TEXTMODE:
		drawText(&ht, point, m_font.text);
		break;
	case POLYGONMODE:
	{
		ASSERT(m_iPolyDotNumbers < 999);
		if (PushNumb == 0) {
			pMain->AddStrOutputDebugWnd(_T("开始绘制任意多边形"));
			m_ptPolyDotArrays[m_iPolyDotNumbers] = point;
			++m_iPolyDotNumbers;
			PushNumb++;
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("（%ld ，%ld）"), point.x, point.y);
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(pointStr);
			SetCapture();
		}
		else {
			m_ptPolyDotArrays[m_iPolyDotNumbers] = point;
			++m_iPolyDotNumbers;
			ht.MoveTo(mPointOrign);
			ht.LineTo(point);
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("（%ld ，%ld）"), point.x, point.y);
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(pointStr);
		}
		break;
	}

	case ERASEMODE:
		if (!mR_ist) {
			m_rO = m_rR = point;
			mR_ist++;
		}
		else {
			m_rR = point;
			mR_ist--;
			//ht.Rectangle(m_rO.x, m_rO.y, m_rR.x, m_rR.y);
			CRect rect(m_rO, m_rR);
			InvalidateRect(rect);
			UpdateData(TRUE);
			CString eraseInfo;
			eraseInfo.Format(_T("已擦除区域：（%ld，%ld）到（%ld，%ld）"), m_rO.x, m_rO.y, m_rR.x, m_rR.y);
			pMain->AddStrOutputDebugWnd(eraseInfo);
			ReleaseCapture();
		}
		break;

	case CURVEMODE:
		if (!curveFlag) {
			mPointOrign = mPointOld = point;
			curveFlag = TRUE;
			SetCapture();
			pMain->AddStrOutputDebugWnd(_T("开始自由绘制"));
		}
		else {
			mPointOrign = mPointOld = point;
			curveFlag = FALSE;
			ReleaseCapture();
			pMain->AddStrOutputDebugWnd(_T("结束自由绘制"));
		}


	default:
		break;
	}
	ht.SelectObject(pOldPen);

	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDrawDoc *pDoc = GetDocument();
	CClientDC ddd(this);
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CPen cPen;
	cPen.CreatePen(penStyle, penWidth, m_color);
	CPen *pOldPen = ddd.SelectObject(&cPen);

	ddd.SetROP2(R2_NOTXORPEN);
	if (m_DrawCurrent == LINEMODE && PushNumb == 1) {
		ddd.MoveTo(mPointOrign);
		ddd.LineTo(mPointOld);
		PushNumb = 0;
		ReleaseCapture();
	}
	if (m_DrawCurrent == PLINEMODE && PushNumb > 0) {
		ddd.MoveTo(mPointOrign);
		ddd.LineTo(mPointOld);
		PushNumb = 0;
		ReleaseCapture();
		pMain->AddStrOutputDebugWnd(_T("多线段绘制结束"));
	}
	if (m_DrawCurrent == CIRCLEMODE && m_ist == 1) {
		ddd.SelectStockObject(NULL_BRUSH);
		drawCircle(&ddd, m_bO, m_bR);
		m_ist = 0;
		ReleaseCapture();

	}
	if (m_DrawCurrent == RECTMODE && mR_ist == 1) {
		ddd.SelectStockObject(NULL_BRUSH);
		drawRect(&ddd, m_rO, m_rR);
		mR_ist = 0;
		ReleaseCapture();
	}
	if (m_DrawCurrent == POLYGONMODE) {
		ddd.SelectStockObject(NULL_BRUSH);
		if (m_iPolyDotNumbers > 2)
		{
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(mPointOld);
			ddd.SetROP2(R2_COPYPEN);
			ddd.Polygon(m_ptPolyDotArrays, m_iPolyDotNumbers);
			m_iPolyDotNumbers = 0;
			PushNumb = 0;
			pMain->AddStrOutputDebugWnd(_T("多边形绘制结束。"));
		}
		else {
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(mPointOld);
			ddd.Polygon(m_ptPolyDotArrays, m_iPolyDotNumbers);
			m_iPolyDotNumbers = 0;
			PushNumb = 0;
			pMain->AddStrOutputDebugWnd(_T("点数小于2，未满足多边形绘制。"));
		}
		ReleaseCapture();
	}
	ddd.SelectObject(pOldPen);

	CView::OnRButtonDown(nFlags, point);
}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	CDrawDoc *pDoc = GetDocument();
	CClientDC ddd(this);
	CPen cPen;
	cPen.CreatePen(penStyle, penWidth, m_color);
	CPen *pOldPen = ddd.SelectObject(&cPen);
	int nDrawMode = ddd.SetROP2(R2_NOTXORPEN);
	if (m_DrawCurrent == LINEMODE && PushNumb == 1) {
		if (mPointOld != point) {
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(mPointOld);
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(point);
			mPointOld = point;
		}
	}
	if (m_DrawCurrent == PLINEMODE && PushNumb > 0) {
		if (mPointOld != point) {
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(mPointOld);
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(point);
			mPointOld = point;
		}
	}
	if (m_DrawCurrent == CIRCLEMODE && m_ist == 1) {
		ddd.SelectStockObject(NULL_BRUSH);
		CPoint prePnt, curPnt;
		prePnt = m_bR;
		curPnt = point;
		drawCircle(&ddd, m_bO, prePnt);
		drawCircle(&ddd, m_bO, curPnt);
		m_bR = point;
		ddd.SetROP2(nDrawMode);
	}
	if (m_DrawCurrent == RECTMODE && mR_ist == 1) {
		ddd.SelectStockObject(NULL_BRUSH);
		CPoint prePnt, curPnt;
		prePnt = m_rR;
		curPnt = point;
		drawRect(&ddd, m_rO, prePnt);
		drawRect(&ddd, m_rO, curPnt);
		m_rR = point;
		ddd.SetROP2(nDrawMode);
	}
	if (m_DrawCurrent == POLYGONMODE && PushNumb > 0) {
		if (mPointOld != point) {
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(mPointOld);
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(point);
			mPointOld = point;
		}
	}
	if (m_DrawCurrent == ERASEMODE && mR_ist == 1) {
		CPen cPen1;
		cPen1.CreatePen(PS_DOT, 1, RGB(255,0,0));
		ddd.SelectObject(&cPen1);
		ddd.SelectStockObject(NULL_BRUSH);
		CPoint prePnt, curPnt;
		prePnt = m_rR;
		curPnt = point;
		//drawRect(&ddd, m_rO, prePnt);
		ddd.Rectangle(m_rO.x, m_rO.y, prePnt.x, prePnt.y);
		//drawRect(&ddd, m_rO, curPnt);
		ddd.Rectangle(m_rO.x, m_rO.y, curPnt.x, curPnt.y);
		m_rR = point;
		ddd.SetROP2(nDrawMode);
	}
	if (m_DrawCurrent == CURVEMODE && curveFlag) {
		ddd.SetROP2(R2_COPYPEN);
		drawCurve(&ddd, mPointOrign, point);
	}
	ddd.SelectObject(pOldPen);
	CView::OnMouseMove(nFlags, point);
}


void CDrawView::drawCircle(CClientDC* ht, CPoint cenp, CPoint ardp)
{
	int radius = computeRadius(cenp, ardp);
	CRect rc(cenp.x - radius, cenp.y - radius, cenp.x + radius, cenp.y + radius);
	ht->Ellipse(rc);
}


int CDrawView::computeRadius(CPoint cenp, CPoint ardp)
{
	int dx = cenp.x - ardp.x;
	int dy = cenp.y - ardp.y;
	return (int)sqrt(dx*dx + dy*dy);
}


void CDrawView::OnDrawCircle()
{
	m_ist = 0;
	m_DrawCurrent = CIRCLEMODE;
}

void CDrawView::OnDrawRectangle()
{
	mR_ist = 0;
	m_DrawCurrent = RECTMODE;
}


void CDrawView::testCircle(CDC* pDC, CPoint cenp, CPoint ardp)
{
	int radius = computeRadius(cenp, ardp);
	CRect rc(cenp.x - radius, cenp.y - radius, cenp.x + radius, cenp.y + radius);
	pDC->Ellipse(rc);
}


void CDrawView::drawRect(CClientDC* ht, CPoint cPoint, CPoint ePoint)
{
	ht->Rectangle(cPoint.x, cPoint.y, ePoint.x, ePoint.y);
}


void CDrawView::OnInsertText()
{
	CTextDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		m_font.text = dlg.getText();
		m_font.size = dlg.getTextSize();
		m_font.faceName = dlg.getTextFont();
		CString fontInfo;
		fontInfo.Format(_T("已选择字体：" + m_font.faceName + "；字号：%d"), m_font.size);
		pMain->AddStrOutputDebugWnd(fontInfo);
		m_DrawCurrent = TEXTMODE;
	}
	else {
		return;
	}

}


void CDrawView::drawText(CClientDC* ht, CPoint curPoint, CString text)
{
	ht->SelectStockObject(NULL_BRUSH);
	if (text == "") return;
	m_font.newFont.CreateFontW(m_font.size,  //字体高度（逻辑单位）
		0,  //字符的平均宽度（逻辑单位）
		0,  //偏离垂线和显示界面X轴之间的角度，以十分之一度为单位。偏离垂线是穿过一行文本中第一个字符和最后一个字符的直线。
		0,  //每个字符的基线和设备X轴之间的角度，以十分之一度为单位。
		FW_NORMAL,  //字体磅数（每1000点中墨点像素数）。可取0到1000之间的任意整数值。
		FALSE, //斜体
		FALSE, //下划线
		0,  //删除线
		ANSI_CHARSET,  //字体的字符集
		OUT_DEFAULT_PRECIS,  //输出精度
		CLIP_DEFAULT_PRECIS,  //裁剪精度
		DEFAULT_QUALITY,  //字体的输出质量
		DEFAULT_PITCH | FF_SWISS,  //字体间距和字体族
		m_font.faceName  //字体的字样名的字符串
	);//创建新字体
	m_font.oldFont = ht->SelectObject(&m_font.newFont);
	ht->SetTextColor(m_color);
	ht->TextOutW(curPoint.x, curPoint.y, text);
	CString outTextInfo;
	outTextInfo.Format(_T("已在（%ld，%ld）位置添加字符：" + text), curPoint.x, curPoint.y);
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(outTextInfo);
	m_DrawCurrent = NULLMODE;
	m_font.text = "";
	ht->SelectObject(m_font.oldFont);
	m_font.newFont.DeleteObject();
}


void CDrawView::OnColorBlack()
{
	m_color = COLOR_BLACK;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局颜色已设置为黑色。"));
}


void CDrawView::OnColorRed()
{
	m_color = COLOR_RED;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局颜色已设置为红色。"));
}


void CDrawView::OnColorGreen()
{
	m_color = COLOR_GREEN;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局颜色已设置为绿色。"));
}


void CDrawView::OnColorBlue()
{
	m_color = COLOR_BLUE;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局颜色已设置为蓝色。"));
}


void CDrawView::OnColorCustom()
{
	CColorDialog m_setClrDlg;
	m_setClrDlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;   // CC_RGBINIT可以让上次选择的颜色作为初始颜色显示出来
	m_setClrDlg.m_cc.rgbResult = m_color;        //记录上次选择的颜色
	if (IDOK == m_setClrDlg.DoModal())
	{
		m_color = m_setClrDlg.m_cc.rgbResult;            // 保存用户选择的颜色
		/*int r = BYTE(m_color);
		int b = BYTE(m_color >> 8);
		int g = BYTE(m_color >> 16);*/
		//int a = BYTE(m_color >> 24);
		int r = GetRValue(m_color);
		int g = GetGValue(m_color);
		int b = GetBValue(m_color);
		CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString colorInfo;
		colorInfo.Format(_T("全局颜色已设置为RGB(%d，%d，%d)。"), r, g, b);
		pMain->AddStrOutputDebugWnd(colorInfo);
	}
}


void CDrawView::OnPenstyleSolid()
{
	penStyle = PS_SOLID;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线性已设置为实线。"));
}


void CDrawView::OnPanstyleDash()
{
	penStyle = PS_DASH;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线性已设置为虚线。"));
}


void CDrawView::OnPanstyleDot()
{
	penStyle = PS_DOT;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线性已设置为点线。"));
}


void CDrawView::OnPanstyleDashdot()
{
	penStyle = PS_DASHDOT;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线性已设置为点划线。"));
}


void CDrawView::OnPanstyleDashdotdot()
{
	penStyle = PS_DASHDOTDOT;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线性已设置为双点划线。"));
}


void CDrawView::OnPenwidthThin()
{
	penWidth = PEN_WIDTH_THIN;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线宽已设置为细线。"));
}


void CDrawView::OnPenwidthMid()
{
	penWidth = PEN_WIDTH_MID;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线宽已设置为中等线。"));
}


void CDrawView::OnPenwidthThick()
{
	penWidth = PEN_WIDTH_THICK;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("全局线宽已设置为粗线。"));
}


void CDrawView::OnPenwidthCustom()
{
	FontWidthCustom dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		penWidth = dlg.getFontWidth();
		CString penWidthInfo;
		penWidthInfo.Format(_T("全局线宽已设置为 %d。"), penWidth);
		CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMain->AddStrOutputDebugWnd(penWidthInfo);
	}
	else {
		return;
	}
}


void CDrawView::OnDrawPolygon()
{
	m_DrawCurrent = POLYGONMODE;
}


void CDrawView::OnEraseAll()
{
	Invalidate();
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("已清空全部图形。"));
	pMain->AddStrOutputDebugWnd(_T(" "));
}


void CDrawView::OnEraseCustom()
{
	m_DrawCurrent = ERASEMODE;
	PushNumb = 0;
}


BOOL CDrawView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(LoadCursor(NULL, IDC_CROSS));
	return TRUE;
	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CDrawView::drawCurve(CClientDC* ht, CPoint first, CPoint second)
{
	ht->MoveTo(first);
	ht->LineTo(second);
	mPointOrign = second;
	mPointOld = second;
}


void CDrawView::OnDrawCustom()
{
	m_DrawCurrent = CURVEMODE;
}
