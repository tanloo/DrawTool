#pragma once


// FontWidthCustom �Ի���

class FontWidthCustom : public CDialogEx
{
	DECLARE_DYNAMIC(FontWidthCustom)

public:
	FontWidthCustom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FontWidthCustom();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	int m_fontWidth;
public:
	int getFontWidth();
};
