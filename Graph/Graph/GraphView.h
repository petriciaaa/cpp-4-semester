
// GraphView.h: интерфейс класса CGraphView
//

#pragma once


class CGraphView : public CView
{
protected: // создать только из сериализации
	CGraphView() noexcept;
	DECLARE_DYNCREATE(CGraphView)

// Атрибуты
public:
	CGraphDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CGraphView();
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

public:

private:
	COLORREF m_graphColor;
	COLORREF m_axisColor;
};

#ifndef _DEBUG  // версия отладки в GraphView.cpp
inline CGraphDoc* CGraphView::GetDocument() const
   { return reinterpret_cast<CGraphDoc*>(m_pDocument); }
#endif

