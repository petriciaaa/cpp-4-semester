
// GraphView.cpp: реализация класса CGraphView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Graph.h"
#endif
#include <math.h>

#include "GraphDoc.h"
#include "GraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphView

IMPLEMENT_DYNCREATE(CGraphView, CView)

BEGIN_MESSAGE_MAP(CGraphView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CGraphView

CGraphView::CGraphView() noexcept {
	m_graphColor = RGB(255, 0, 0); // Красный график
	m_axisColor = RGB(0, 0, 255);  // Синие оси и сетка
}

CGraphView::~CGraphView()
{
}

BOOL CGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CGraphView

void CGraphView::OnDraw(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);

    // Белый фон
    pDC->FillSolidRect(rect, RGB(255, 255, 255));

    const int width = rect.Width();
    const int height = rect.Height();
    const int centerX = width / 2;
    const int centerY = height / 2;

    // Отрисовка сетки
    CPen gridPen(PS_DOT, 1, m_axisColor);
    CPen* pOldPen = pDC->SelectObject(&gridPen);

    for (int x = 0; x < width; x += 50)
    {
        pDC->MoveTo(x, 0);
        pDC->LineTo(x, height);
    }
    for (int y = 0; y < height; y += 50)
    {
        pDC->MoveTo(0, y);
        pDC->LineTo(width, y);
    }

    // Оси координат
    CPen axisPen(PS_SOLID, 2, m_axisColor);
    pDC->SelectObject(&axisPen);

    // X-ось
    pDC->MoveTo(0, centerY);
    pDC->LineTo(width, centerY);

    // Y-ось
    pDC->MoveTo(centerX, 0);
    pDC->LineTo(centerX, height);

    // График функции sin(x)
    CPen graphPen(PS_SOLID, 2, m_graphColor);
    pDC->SelectObject(&graphPen);

    // Масштаб по X и Y
    double scaleX = 0.05; // Чем меньше — тем шире график
    double scaleY = 50.0; // Амплитуда в пикселях

    bool firstPoint = true;
    for (int x = 0; x < width; ++x)
    {
        double xValue = (x - centerX) * scaleX;
        double yValue = sin(xValue);
        int y = static_cast<int>(centerY - yValue * scaleY);

        if (firstPoint)
        {
            pDC->MoveTo(x, y);
            firstPoint = false;
        }
        else
        {
            pDC->LineTo(x, y);
        }
    }

    pDC->SelectObject(pOldPen);
}

void CGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Меняем местами цвета графика и осей
    COLORREF tmp = m_graphColor;
    m_graphColor = m_axisColor;
    m_axisColor = tmp;

    Invalidate(); // Перерисовать окно
    CView::OnLButtonDown(nFlags, point);
}
// Печать CGraphView


void CGraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CGraphView

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphDoc* CGraphView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphDoc)));
	return (CGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CGraphView
