
// MFCMyFirstApplicationDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMFCMyFirstApplicationDlg
class CMFCMyFirstApplicationDlg : public CDialogEx
{
// Создание
public:
	CMFCMyFirstApplicationDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMYFIRSTAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnMessage();
	afx_msg void OnBnClickedBtnBeep();
	afx_msg void OnBnClickedBtnExit();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
