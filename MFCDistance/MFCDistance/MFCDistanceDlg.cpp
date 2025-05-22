
// MFCDistanceDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCDistance.h"
#include "MFCDistanceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CMFCDistanceDlg



CMFCDistanceDlg::CMFCDistanceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDISTANCE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDistanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_M1, m_1);
	DDX_Text(pDX, IDC_EDIT_C1, c_1);
	DDX_Text(pDX, IDC_EDIT_M2, m_2);
	DDX_Text(pDX, IDC_EDIT_C2, c_2);
	DDX_Text(pDX, IDC_EDIT_M3, m_3);
	DDX_Text(pDX, IDC_EDIT_C3, c_3);
}

BEGIN_MESSAGE_MAP(CMFCDistanceDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCDistanceDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CMFCDistanceDlg::OnBnClickedSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CMFCDistanceDlg::OnBnClickedMul)
	ON_BN_CLICKED(IDCANCEL, &CMFCDistanceDlg::OnBnClickedReset)
END_MESSAGE_MAP()

void CMFCDistanceDlg::UpdateResult(const Distance& d3) {
	m_3 = d3.get_met();
	c_3 = d3.get_cent();
	UpdateData(FALSE);
}

void CMFCDistanceDlg::OnBnClickedAdd() {
	UpdateData(TRUE);
	Distance d1(m_1, c_1), d2(m_2, c_2), d3;
	d3 = d1 + d2;
	UpdateResult(d3);
}

void CMFCDistanceDlg::OnBnClickedSub() {
	UpdateData(TRUE);
	Distance d1(m_1, c_1), d2(m_2, c_2), d3;
	d3 = d1 - d2;
	UpdateResult(d3);
}

void CMFCDistanceDlg::OnBnClickedMul() {
	UpdateData(TRUE);
	Distance d1(m_1, c_1), d2(m_2, c_2), d3;
	d3 = d1 * d2;
	UpdateResult(d3);
}

void CMFCDistanceDlg::OnBnClickedReset() {
	Distance zero;
	m_1 = m_2 = m_3 = 0;
	c_1 = c_2 = c_3 = 0.0f;
	UpdateData(FALSE);
}

void CMFCDistanceDlg::OnOK() {
	CDialogEx::OnOK();
}
// Обработчики сообщений CMFCDistanceDlg

BOOL CMFCDistanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCDistanceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCDistanceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCDistanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


