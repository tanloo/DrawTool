#pragma once


// FontWidthCustom 对话框

class FontWidthCustom : public CDialogEx
{
	DECLARE_DYNAMIC(FontWidthCustom)

public:
	FontWidthCustom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FontWidthCustom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_fontWidth;
public:
	int getFontWidth();
};
