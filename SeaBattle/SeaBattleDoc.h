
// SeaBattleDoc.h: интерфейс класса CSeaBattleDoc 
//


#pragma once
#include "CGameBoard.h"


class CSeaBattleDoc : public CDocument
{
protected: // создать только из сериализации
	CSeaBattleDoc() noexcept;
	DECLARE_DYNCREATE(CSeaBattleDoc)

// Атрибуты
public:

// Операции
public:
	//Функция получения значения в заданной ячейке на поле соперника
	int GetBoardSpace(int row, int col)
	{
		return m_board.GetBoardSpace(row, col);
	}
	//Функция получения значения в заданной ячейке на поле игрока
	int GetBoardSelfSpace(int row, int col)
	{
		return m_board.GetBoardSelfSpace(row, col);
	}
	void SetupEnemy(void) { m_board.SetupEnemy(); }  //Функция заполнения поля соперника
	void SetupSelf(void) { m_board.SetupSelf(); } //Функция заполнения поля игрока
	//Функция установки значения в заданную ячейку поля соперника
	void SetBoardSpace(int i, int j, int value) { 
		m_board.SetBoardSpace(i, j, value); 
	}
	//Функция установки значения в заданную ячейку поля игрока
	void SetBoardSelfSpace(int i, int j, int value) { 
		m_board.SetBoardSelfSpace(i, j, value); 
	}
	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeight(); }
	int GetColumns(void) { return m_board.GetColumn(); }
	int GetRows(void) { return m_board.GetRow(); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }
	void SelfDecrease(void) { return m_board.SelfDecrease(); }
	void EnemyDecrease(void) { return m_board.EnemyDecrease(); }
	int DefineWinner(void) { return m_board.DefineWinner(); }
	void RepaintDeadEnemy(int row, int col) { return m_board.RepaintDeadEnemy(row, col); }
	void RepaintDeadSelf(int row, int col) { return m_board.RepaintDeadSelf(row, col); }
	bool EnemyMove(void) { return m_board.EnemyMove(); }
	void SetEnemyReamin(int x) { return m_board.SetEnemyReamin(x); };
	void SetSelfRemain(int x) { return m_board.SetSelfRemain(x); };

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSeaBattleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CGameBoard m_board;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
