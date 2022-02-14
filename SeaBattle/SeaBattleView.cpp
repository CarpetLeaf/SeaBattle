
// SeaBattleView.cpp: реализация класса CSeaBattleView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SeaBattle.h"
#endif

#include "SeaBattleDoc.h"
#include "SeaBattleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeaBattleView

IMPLEMENT_DYNCREATE(CSeaBattleView, CView)

BEGIN_MESSAGE_MAP(CSeaBattleView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_SAVE, &CSeaBattleView::OnSave)
	ON_COMMAND(ID_NEWGAME, &CSeaBattleView::OnNewgame)
	ON_COMMAND(ID_LOAD, &CSeaBattleView::OnLoad)
END_MESSAGE_MAP()

// Создание или уничтожение CSeaBattleView

CSeaBattleView::CSeaBattleView() noexcept
{
	// TODO: добавьте код создания

}

CSeaBattleView::~CSeaBattleView()
{
}

BOOL CSeaBattleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSeaBattleView

void CSeaBattleView::OnDraw(CDC* pDC)
{
	CSeaBattleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	int save = pDC->SaveDC();
	COLORREF m_Colors[5];
	m_Colors[0] = RGB(30, 144, 255); //Цвет фона
	m_Colors[2] = RGB(128, 128, 128); //Цвет промаха
	m_Colors[1] = RGB(124, 252, 0); //Цвет собственного корабля
	m_Colors[3] = RGB(255, 255, 0); //Цвет попадания
	m_Colors[4] = RGB(124, 10, 2); //Цвет убитого корабля
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF color = pDoc->GetBoardSpace(-1, -1);
	pDC->FillSolidRect(&rcClient, color);
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* brOld = pDC->SelectObject(&br);

	for (int i = 0; i < pDoc->GetRows(); i++)
	{
		for (int j = 0; j < pDoc->GetColumns(); j++)
		{
			if (pDoc->GetBoardSpace(i, j) == 1)
				color = m_Colors[0];
			else color = m_Colors[pDoc->GetBoardSpace(i, j)];
			CRect rcBlock;
			rcBlock.top = i * pDoc->GetHeight();
			rcBlock.left = j * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			pDC->FillSolidRect(&rcBlock, color);
			pDC->Rectangle(&rcBlock);
		}
	}

	int space = 250;
	for (int i = 0; i < pDoc->GetRows(); i++) {
		for (int j = 0; j < pDoc->GetColumns(); j++) {
			color = m_Colors[pDoc->GetBoardSelfSpace(i, j)];
			CRect rcBlock;
			rcBlock.top = i * pDoc->GetHeight();
			rcBlock.left = j * pDoc->GetWidth() + space;
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			pDC->FillSolidRect(&rcBlock, color);
			pDC->Rectangle(&rcBlock);
		}
	}
	pDC->RestoreDC(save);
	br.DeleteObject();
}


// Диагностика CSeaBattleView

#ifdef _DEBUG
void CSeaBattleView::AssertValid() const
{
	CView::AssertValid();
}

void CSeaBattleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSeaBattleDoc* CSeaBattleView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeaBattleDoc)));
	return (CSeaBattleDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSeaBattleView


void CSeaBattleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: добавьте специализированный код или вызов базового класса
	ResizeWindow();
}

//Функция подгонки размера окна
void CSeaBattleView::ResizeWindow()
{
	CSeaBattleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns()*2+50 + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CSeaBattleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CSeaBattleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->DefineWinner() == 0) {  //Если игра еще продолжается, обрабатываем нажатие кнопки
		if (point.x <= pDoc->GetWidth() * 10 && point.y <= pDoc->GetHeight() * 10) {
			COLORREF m_Colors[5];
			m_Colors[0] = RGB(30, 144, 255); //Цвет фона
			m_Colors[2] = RGB(128, 128, 128); //Цвет промаха
			m_Colors[1] = RGB(124, 252, 0); //Цвет собственного корабля
			m_Colors[3] = RGB(255, 255, 0); //Цвет попадания
			m_Colors[4] = RGB(124, 10, 2); //Цвет убитого корабля

			int i = point.y / pDoc->GetHeight();
			int j = point.x / pDoc->GetWidth();
			if (pDoc->GetBoardSpace(i, j) == 0) {
				pDoc->SetBoardSpace(i, j, 2);
				Invalidate();
				UpdateWindow();
				bool res = pDoc->EnemyMove();
				//Пока соперник попадает по кораблям игрока, соперник делает ход
				while (res) {
					pDoc->SelfDecrease();
					if (pDoc->DefineWinner() > 0) {
						CString message;
						message.Format(_T("Вы победили"));
						MessageBox(message, _T("Игра Закончена "), MB_OK | MB_ICONINFORMATION);
						break;
					}
					else if (pDoc->DefineWinner() < 0) {
						CString message;
						message.Format(_T("Вы проиграли"));
						MessageBox(message, _T("Игра Закончена "), MB_OK | MB_ICONINFORMATION);
						break;
					}
					res = pDoc->EnemyMove();
				}
				Invalidate();
				UpdateWindow();
			}
			if (pDoc->GetBoardSpace(i, j) == 1) {
				pDoc->SetBoardSpace(i, j, 3);
				pDoc->RepaintDeadEnemy(i, j);
				Invalidate();
				UpdateWindow();
				pDoc->EnemyDecrease();
				if (pDoc->DefineWinner() > 0) {
					CString message;
					message.Format(_T("Вы победили"));
					MessageBox(message, _T("Игра Закончена "), MB_OK | MB_ICONINFORMATION);
				}
				else if (pDoc->DefineWinner() < 0) {
					CString message;
					message.Format(_T("Вы проиграли"));
					MessageBox(message, _T("Игра Закончена "), MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

//Функция сохранения текущей игры
void CSeaBattleView::OnSave()
{
	// TODO: добавьте свой код обработчика команд
	CSeaBattleDoc* pDoc = GetDocument();
	CFile cfile;
	cfile.Open(_T("Results.txt"), CFile::modeCreate |
		CFile::modeReadWrite);
	char res[200];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			res[10 * i + j] = '0' + pDoc->GetBoardSpace(i, j);
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			res[100+10 * i + j] = '0' + pDoc->GetBoardSelfSpace(i, j);
		}
	}
	cfile.Write(res, sizeof(res));
	cfile.Flush();
}



//Функция запуска новой игры
void CSeaBattleView::OnNewgame()
{
	// TODO: добавьте свой код обработчика команд
	CSeaBattleDoc* pDoc = GetDocument();
	pDoc->SetupEnemy();
	pDoc->SetupSelf();
	Invalidate();
	UpdateWindow();
}

//Функция запуска сохраненной игры
void CSeaBattleView::OnLoad()
{
	// TODO: добавьте свой код обработчика команд
	CSeaBattleDoc* pDoc = GetDocument();
	CFile cfile;
	cfile.Open(_T("Results.txt"), CFile::modeNoTruncate |
		CFile::modeReadWrite);
	char check[2];
	if (cfile.Read(check, 2) == 2) {
		char read[200];
		cfile.Read(read, sizeof(read));
		int k = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				int x = read[i * 10 + j] - '0';
				if (x == 4)
					k++;
				pDoc->SetBoardSpace(i, j, x);
			}
		}
		pDoc->SetEnemyReamin(20 - k);
		k = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				int x = read[100 + i * 10 + j] - '0';
				if (x == 4)
					k++;
				pDoc->SetBoardSelfSpace(i, j, x);
			}
		}
		pDoc->SetSelfRemain(20 - k);
		Invalidate();
		UpdateWindow();
	}
}
