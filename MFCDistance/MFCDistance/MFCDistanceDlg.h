
// MFCDistanceDlg.h: файл заголовка
//
#include "Distance.h"
#pragma once


// Диалоговое окно CMFCDistanceDlg
class CMFCDistanceDlg : public CDialogEx
{
// Создание
public:
	CMFCDistanceDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDISTANCE_DIALOG };
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
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedSub();
	afx_msg void OnBnClickedMul();
	afx_msg void OnBnClickedReset();
	virtual void OnOK();
	void UpdateResult(const Distance& d3);

	int m_1, m_2, m_3;
	float c_1, c_2, c_3;
};
