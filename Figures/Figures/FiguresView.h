
// FiguresView.h: интерфейс класса CFiguresView
//

#pragma once
#include <vector>

enum class ShapeType { Triangle, Circle };

struct Shape {
	ShapeType type;
	CPoint position;
	COLORREF color;
	int size; // для круга — радиус, для треугольника — длина стороны
};

class CFiguresView : public CView
{
protected: // создать только из сериализации
	CFiguresView() noexcept;
	DECLARE_DYNCREATE(CFiguresView)

// Атрибуты
public:
	CFiguresDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CFiguresView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	std::vector<Shape> m_shapes;

	COLORREF GenerateRandomColor();
	int GenerateRandomSize(int min, int max);
};

#ifndef _DEBUG  // версия отладки в FiguresView.cpp
inline CFiguresDoc* CFiguresView::GetDocument() const
   { return reinterpret_cast<CFiguresDoc*>(m_pDocument); }
#endif

