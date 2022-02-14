#pragma once
class CGameBoard
{
public:
	CGameBoard(void); //Конструктор

	~CGameBoard(void); //Деструктор

	void SetupEnemy(void); //Функция расстановки кораблей соперника

	void SetupSelf(void); // Функция расстановки собственных кораблей

	int GetWidth(void) const { return m_nWidth; }  //Функия получения ширины ячейки
	int GetHeight(void) const { return m_nHeight; }  //Функция получения высоты ячейки
	int GetColumn(void) const { return m_nColumn; }  //Функция получения индекса столбца
	int GetRow(void) const { return m_nRow; }  //Функция получения индекса строки

	void DeleteBoard(void);  //Функция удаления игрового поля соперника
	void DeleteBoardSelf(void);  //Функция удаления игрового поля игрока
	int GetBoardSpace(int row, int col); //Функция получения значения из заданной ячейки поля соперника
	int GetBoardSelfSpace(int row, int col);  //Функция получения значения из заданной ячейки поля игрока
	void SetBoardSpace(int row, int col, int value);  //Функция установки заданного значения в соответсвующую ячейку поля соперника
	void SetBoardSelfSpace(int row, int col, int value);  //Функция установки заданного значения в соответсвующую ячейку поля игрока
	void SelfDecrease(void);  //Уменьшение неподбитых частей кораблей на 1 у игрока
	void EnemyDecrease(void);  //Уменьшение неподбитых частей кораблей на 1 у соперника
	int DefineWinner(void);  //Функция определения победителя
	void RepaintDeadEnemy(int row, int col);  //Функция перерисовки корабля у соперника, если он был уничтожен
	void RepaintDeadSelf(int row, int col);  //Функция перерисовки корабля у игрока, если он был уничтожен
	bool EnemyMove(void);  //Функция, описывающая ход соперника
	void SetEnemyReamin(int x);  //Функция установки количества неподбитых кораблей у соперника
	void SetSelfRemain(int x);  //Функция установки количества неподбитых кораблей у игрока

	
private:
	void CreateBoard(void);  //Функция создания игрового поля соперника
	void CreateBoardSelf(void);  //Функция создания игрового поля игрока
	int** m_arrBoard;       //Массив вражеского поля
	int** m_arrBoardSelf;   //Массив поля игрока

	int m_nWidth;  //Ширина ячейки
	int m_nHeight;  //Высота ячейки
	int m_nColumn;  //Индекс столбца
	int m_nRow;  //Индекс строки
	int m_selfRemain;  //Остаток неподбитых частей кораблей игрока
	int m_enemyRemain;  //Остаток неподбитых частей кораблей соперника
};

