
// SeaBattleView.h: интерфейс класса CSeaBattleView
//

#pragma once


class CSeaBattleView : public CView
{
protected: // создать только из сериализации
	CSeaBattleView() noexcept;
	DECLARE_DYNCREATE(CSeaBattleView)

// Атрибуты
public:
	CSeaBattleDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	void ResizeWindow();
	virtual ~CSeaBattleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSave();
	afx_msg void OnNewgame();
	afx_msg void OnLoad();
};

#ifndef _DEBUG  // версия отладки в SeaBattleView.cpp
inline CSeaBattleDoc* CSeaBattleView::GetDocument() const
   { return reinterpret_cast<CSeaBattleDoc*>(m_pDocument); }
#endif

