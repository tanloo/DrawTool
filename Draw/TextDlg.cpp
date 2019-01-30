// TextDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Draw.h"
#include "TextDlg.h"
#include "afxdialogex.h"


// CTextDlg �Ի���

IMPLEMENT_DYNAMIC(CTextDlg, CDialogEx)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INSERT_TEXT, pParent)
	, text(_T("��������ʲô����"))
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


// CTextDlg ��Ϣ�������


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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


BOOL CTextDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	textFont.AddString(_T("����"));
	textFont.AddString(_T("����"));
	textFont.AddString(_T("΢���ź�"));
	textFont.AddString(_T("����"));
	textFont.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
