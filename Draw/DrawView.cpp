
// DrawView.cpp : CDrawView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CDrawView ����/����
CDrawView::CDrawView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	
	return CView::PreCreateWindow(cs);
}

// CDrawView ����

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//pDC->SelectStockObject(NULL_BRUSH);
	//testCircle(pDC, m_bO, m_bR);
}


// CDrawView ��ӡ


void CDrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CDrawView ���

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView ��Ϣ�������


void CDrawView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
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
	CDocument::SetTitle(L"��»��");
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
			pMain->AddStrOutputDebugWnd(_T("��ʼ���Ƶ��߶�"));
			PushNumb++;
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("��%ld ��%ld��"), point.x, point.y);
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(pointStr);
			SetCapture();
		}
		else if (PushNumb == 1) {
			ht.MoveTo(mPointOrign);
			ht.LineTo(point);
			PushNumb = 0;
			CString pointInfo, mPointOrignStr, mPointOldStr;
			mPointOrignStr.Format(_T("��%ld ��%ld��"), mPointOrign.x, mPointOrign.y);
			mPointOldStr.Format(_T("��%ld ��%ld��"), mPointOld.x, mPointOld.y);
			pointInfo = _T("�����ߵ������") + mPointOrignStr + "��" + mPointOldStr;
			UpdateData(TRUE);
			pMain->AddStrOutputDebugWnd(mPointOldStr);
			pMain->AddStrOutputDebugWnd(pointInfo);
			ReleaseCapture();
		}
		break;
	case PLINEMODE:
		if (PushNumb == 0) {
			pMain->AddStrOutputDebugWnd(_T("��ʼ���ƶ��߶�"));
			PushNumb++;
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("��%ld ��%ld��"), point.x, point.y);
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
			pointStr.Format(_T("��%ld ��%ld��"), point.x, point.y);
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
			circleInfo.Format(_T("Բ���ƽ�����Բ��Ϊ��%ld��%ld�����뾶Ϊ %d"), m_bO.x, m_bO.y, computeRadius(m_bO, m_bR));
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
			rectInfo.Format(_T("���λ��ƽ��������ĵ�Ϊ��%ld��%ld�����߳�Ϊ %d"), m_rO.x, m_rO.y, computeRadius(m_rO, m_rR) * 2);
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
			pMain->AddStrOutputDebugWnd(_T("��ʼ������������"));
			m_ptPolyDotArrays[m_iPolyDotNumbers] = point;
			++m_iPolyDotNumbers;
			PushNumb++;
			mPointOrign = point;
			mPointOld = point;
			CString pointStr;
			pointStr.Format(_T("��%ld ��%ld��"), point.x, point.y);
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
			pointStr.Format(_T("��%ld ��%ld��"), point.x, point.y);
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
			eraseInfo.Format(_T("�Ѳ������򣺣�%ld��%ld������%ld��%ld��"), m_rO.x, m_rO.y, m_rR.x, m_rR.y);
			pMain->AddStrOutputDebugWnd(eraseInfo);
			ReleaseCapture();
		}
		break;

	case CURVEMODE:
		if (!curveFlag) {
			mPointOrign = mPointOld = point;
			curveFlag = TRUE;
			SetCapture();
			pMain->AddStrOutputDebugWnd(_T("��ʼ���ɻ���"));
		}
		else {
			mPointOrign = mPointOld = point;
			curveFlag = FALSE;
			ReleaseCapture();
			pMain->AddStrOutputDebugWnd(_T("�������ɻ���"));
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
		pMain->AddStrOutputDebugWnd(_T("���߶λ��ƽ���"));
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
			pMain->AddStrOutputDebugWnd(_T("����λ��ƽ�����"));
		}
		else {
			ddd.MoveTo(mPointOrign);
			ddd.LineTo(mPointOld);
			ddd.Polygon(m_ptPolyDotArrays, m_iPolyDotNumbers);
			m_iPolyDotNumbers = 0;
			PushNumb = 0;
			pMain->AddStrOutputDebugWnd(_T("����С��2��δ�������λ��ơ�"));
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
		fontInfo.Format(_T("��ѡ�����壺" + m_font.faceName + "���ֺţ�%d"), m_font.size);
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
	m_font.newFont.CreateFontW(m_font.size,  //����߶ȣ��߼���λ��
		0,  //�ַ���ƽ����ȣ��߼���λ��
		0,  //ƫ�봹�ߺ���ʾ����X��֮��ĽǶȣ���ʮ��֮һ��Ϊ��λ��ƫ�봹���Ǵ���һ���ı��е�һ���ַ������һ���ַ���ֱ�ߡ�
		0,  //ÿ���ַ��Ļ��ߺ��豸X��֮��ĽǶȣ���ʮ��֮һ��Ϊ��λ��
		FW_NORMAL,  //���������ÿ1000����ī��������������ȡ0��1000֮�����������ֵ��
		FALSE, //б��
		FALSE, //�»���
		0,  //ɾ����
		ANSI_CHARSET,  //������ַ���
		OUT_DEFAULT_PRECIS,  //�������
		CLIP_DEFAULT_PRECIS,  //�ü�����
		DEFAULT_QUALITY,  //������������
		DEFAULT_PITCH | FF_SWISS,  //�������������
		m_font.faceName  //��������������ַ���
	);//����������
	m_font.oldFont = ht->SelectObject(&m_font.newFont);
	ht->SetTextColor(m_color);
	ht->TextOutW(curPoint.x, curPoint.y, text);
	CString outTextInfo;
	outTextInfo.Format(_T("���ڣ�%ld��%ld��λ������ַ���" + text), curPoint.x, curPoint.y);
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
	pMain->AddStrOutputDebugWnd(_T("ȫ����ɫ������Ϊ��ɫ��"));
}


void CDrawView::OnColorRed()
{
	m_color = COLOR_RED;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ����ɫ������Ϊ��ɫ��"));
}


void CDrawView::OnColorGreen()
{
	m_color = COLOR_GREEN;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ����ɫ������Ϊ��ɫ��"));
}


void CDrawView::OnColorBlue()
{
	m_color = COLOR_BLUE;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ����ɫ������Ϊ��ɫ��"));
}


void CDrawView::OnColorCustom()
{
	CColorDialog m_setClrDlg;
	m_setClrDlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;   // CC_RGBINIT�������ϴ�ѡ�����ɫ��Ϊ��ʼ��ɫ��ʾ����
	m_setClrDlg.m_cc.rgbResult = m_color;        //��¼�ϴ�ѡ�����ɫ
	if (IDOK == m_setClrDlg.DoModal())
	{
		m_color = m_setClrDlg.m_cc.rgbResult;            // �����û�ѡ�����ɫ
		/*int r = BYTE(m_color);
		int b = BYTE(m_color >> 8);
		int g = BYTE(m_color >> 16);*/
		//int a = BYTE(m_color >> 24);
		int r = GetRValue(m_color);
		int g = GetGValue(m_color);
		int b = GetBValue(m_color);
		CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString colorInfo;
		colorInfo.Format(_T("ȫ����ɫ������ΪRGB(%d��%d��%d)��"), r, g, b);
		pMain->AddStrOutputDebugWnd(colorInfo);
	}
}


void CDrawView::OnPenstyleSolid()
{
	penStyle = PS_SOLID;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ������������Ϊʵ�ߡ�"));
}


void CDrawView::OnPanstyleDash()
{
	penStyle = PS_DASH;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ������������Ϊ���ߡ�"));
}


void CDrawView::OnPanstyleDot()
{
	penStyle = PS_DOT;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ������������Ϊ���ߡ�"));
}


void CDrawView::OnPanstyleDashdot()
{
	penStyle = PS_DASHDOT;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ������������Ϊ�㻮�ߡ�"));
}


void CDrawView::OnPanstyleDashdotdot()
{
	penStyle = PS_DASHDOTDOT;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ������������Ϊ˫�㻮�ߡ�"));
}


void CDrawView::OnPenwidthThin()
{
	penWidth = PEN_WIDTH_THIN;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ���߿�������Ϊϸ�ߡ�"));
}


void CDrawView::OnPenwidthMid()
{
	penWidth = PEN_WIDTH_MID;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ���߿�������Ϊ�е��ߡ�"));
}


void CDrawView::OnPenwidthThick()
{
	penWidth = PEN_WIDTH_THICK;
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMain->AddStrOutputDebugWnd(_T("ȫ���߿�������Ϊ���ߡ�"));
}


void CDrawView::OnPenwidthCustom()
{
	FontWidthCustom dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		penWidth = dlg.getFontWidth();
		CString penWidthInfo;
		penWidthInfo.Format(_T("ȫ���߿�������Ϊ %d��"), penWidth);
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
	pMain->AddStrOutputDebugWnd(_T("�����ȫ��ͼ�Ρ�"));
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
