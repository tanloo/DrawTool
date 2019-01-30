// TextDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Draw.h"
#include "TextDlg.h"
#include "afxdialogex.h"


// CTextDlg 对话框

IMPLEMENT_DYNAMIC(CTextDlg, CDialogEx)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INSERT_TEXT, pParent)
	, text(_T("随便输入点什么。。"))
	, textSize(12)
	, font(_T(""))
{
	
}

CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, text);
	DDX_Text(pDX, IDC_EDIT_TEXTSIZE, textSize);
	DDV_MinMaxInt(pDX, textSize, 0, 99);
	//  DDX_Control(pDX, IDC_COMBO_TEXTFONT, textFont);
	DDX_Control(pDX, IDC_COMBO_TEXTFONTS, textFont);
	DDX_CBString(pDX, IDC_COMBO_TEXTFONTS, font);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_TEXTFONTS, &CTextDlg::OnCbnSelchangeComboTextfont)
END_MESSAGE_MAP()


// CTextDlg 消息处理程序


CString CTextDlg::getText()
{
	return text;
}


int CTextDlg::getTextSize()
{
	return textSize;
}


CString CTextDlg::getTextFont()
{
	//bool b = GetDlgItem(IDC_COMBO_TEXTFONTS)->GetSafeHwnd();

	/*int nIndex = textFont.GetCurSel();
	CString strCBText;
	textFont.GetLBText(nIndex, strCBText);*/
	return font;
}


void CTextDlg::OnCbnSelchangeComboTextfont()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


BOOL CTextDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	textFont.AddString(_T("宋体"));
	textFont.AddString(_T("楷体"));
	textFont.AddString(_T("微软雅黑"));
	textFont.AddString(_T("黑体"));
	textFont.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
