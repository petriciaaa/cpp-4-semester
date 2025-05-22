
// MFCCalcDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCCalc.h"
#include "MFCCalcDlg.h"
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


// Диалоговое окно CMFCCalcDlg



CMFCCalcDlg::CMFCCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCALC_DIALOG, pParent)
	, m_1(0)
	, m_2(0)
	, m_3(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_1);
	DDX_Text(pDX, IDC_EDIT2, m_2);
	DDX_Text(pDX, IDC_EDIT3, m_3);
}

BEGIN_MESSAGE_MAP(CMFCCalcDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CMFCCalcDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BTN_SUB, &CMFCCalcDlg::OnBnClickedSub)
	ON_BN_CLICKED(IDC_BTN_MUL, &CMFCCalcDlg::OnBnClickedMul)
	ON_BN_CLICKED(IDC_BTN_DIV, &CMFCCalcDlg::OnBnClickedDiv)
END_MESSAGE_MAP()

void CMFCCalcDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	m_3 = m_1 + m_2;
	UpdateResult();
}

void CMFCCalcDlg::OnBnClickedSub()
{
	UpdateData(TRUE);
	m_3 = m_1 - m_2;
	UpdateResult();
}

void CMFCCalcDlg::OnBnClickedMul()
{
	UpdateData(TRUE);
	m_3 = m_1 * m_2;
	UpdateResult();
}

void CMFCCalcDlg::OnBnClickedDiv()
{
	UpdateData(TRUE);
	if (m_2 == 0.0)
	{
		MessageBeep(MB_ICONERROR);
		MessageBoxW(L"Деление на ноль невозможно!", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}
	m_3 = m_1 / m_2;
	UpdateResult();
}

void CMFCCalcDlg::UpdateResult()
{
	CString str;
	str.Format(L"%.2f", m_3);
	SetDlgItemTextW(IDC_EDIT3, str);
}


// Обработчики сообщений CMFCCalcDlg

BOOL CMFCCalcDlg::OnInitDialog()
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
	SetWindowTextW(L"Калькулятор");
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCCalcDlg::OnPaint()
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
HCURSOR CMFCCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCCalcDlg::OnEnChangeEdit3()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CMFCCalcDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
