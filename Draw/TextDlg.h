#pragma once
#include "afxwin.h"


// CTextDlg 对话框

class CTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_TEXT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
