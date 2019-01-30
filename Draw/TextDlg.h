#pragma once
#include "afxwin.h"


// CTextDlg �Ի���

class CTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_TEXT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString text;
	int textSize;
//	CComboBox textFont;
public:
	CString getText();
	int getTextSize();
	CString getTextFont();
	afx_msg void OnCbnSelchangeComboTextfont();
private:
	CString font;
	
public:
	virtual BOOL OnInitDialog();
	
	CComboBox textFont;
};
