
// FiguresView.cpp: реализация класса CFiguresView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Figures.h"
#endif

#include "FiguresDoc.h"
#include "FiguresView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFiguresView

IMPLEMENT_DYNCREATE(CFiguresView, CView)

BEGIN_MESSAGE_MAP(CFiguresView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFiguresView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CFiguresView

CFiguresView::CFiguresView() noexcept
{
	// TODO: добавьте код создания

}

CFiguresView::~CFiguresView()
{
}

BOOL CFiguresView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CFiguresView
void CFiguresView::OnDraw(CDC* pDC)
{
    for (const auto& shape : m_shapes)
    {
        CBrush brush(shape.color);
        CBrush* pOldBrush = pDC->SelectObject(&brush);
        CPen pen(PS_SOLID, 1, shape.color);
        CPen* pOldPen = pDC->SelectObject(&pen);

        if (shape.type == ShapeType::Triangle)
        {
            CPoint points[3];
            int half = shape.size / 2;
            points[0] = CPoint(shape.position.x, shape.position.y - shape.size);
            points[1] = CPoint(shape.position.x - half, shape.position.y + half);
            points[2] = CPoint(shape.position.x + half, shape.position.y + half);
            pDC->Polygon(points, 3);
        }
        else if (shape.type == ShapeType::Circle)
        {
            pDC->Ellipse(shape.position.x - shape.size, shape.position.y - shape.size,
                shape.position.x + shape.size, shape.position.y + shape.size);
        }

        pDC->SelectObject(pOldBrush);
        pDC->SelectObject(pOldPen);
    }
}

void CFiguresView::OnLButtonDown(UINT nFlags, CPoint point)
{
    Shape triangle;
    triangle.type = ShapeType::Triangle;
    triangle.position = point;
    triangle.color = GenerateRandomColor();
    triangle.size = GenerateRandomSize(30, 80);

    m_shapes.push_back(triangle);
    Invalidate();
    CView::OnLButtonDown(nFlags, point);
}

void CFiguresView::OnRButtonDown(UINT nFlags, CPoint point)
{
    Shape circle;
    circle.type = ShapeType::Circle;
    circle.position = point;
    circle.color = GenerateRandomColor();
    circle.size = 40; 

    m_shapes.push_back(circle);
    Invalidate(); 
    CView::OnRButtonDown(nFlags, point);
}

COLORREF CFiguresView::GenerateRandomColor()
{
  
    return RGB(rand() % 256, rand() % 256, rand() % 256);
}

int CFiguresView::GenerateRandomSize(int min, int max)
{
    return min + rand() % (max - min + 1);

}

// Печать CFiguresView


void CFiguresView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFiguresView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CFiguresView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CFiguresView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CFiguresView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFiguresView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}


// Диагностика CFiguresView

#ifdef _DEBUG
void CFiguresView::AssertValid() const
{
	CView::AssertValid();
}

void CFiguresView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFiguresDoc* CFiguresView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFiguresDoc)));
	return (CFiguresDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CFiguresView
