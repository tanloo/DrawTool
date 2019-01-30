// FontWidthCustom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Draw.h"
#include "FontWidthCustom.h"
#include "afxdialogex.h"


// FontWidthCustom �Ի���

IMPLEMENT_DYNAMIC(FontWidthCustom, CDialogEx)

FontWidthCustom::FontWidthCustom(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_fontWidth(0)
{

}

FontWidthCustom::~FontWidthCustom()
{
}

void FontWidthCustom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fontWidth);
	DDV_MinMaxInt(pDX, m_fontWidth, 1, 50);
}


BEGIN_MESSAGE_MAP(FontWidthCustom, CDialogEx)
END_MESSAGE_MAP()


// FontWidthCustom ��Ϣ�������


int FontWidthCustom::getFontWidth()
{
	return m_fontWidth;
}
