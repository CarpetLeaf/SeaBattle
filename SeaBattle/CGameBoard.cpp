#include "pch.h"
#include "CGameBoard.h"

CGameBoard::CGameBoard(void)
	: m_arrBoard(NULL),
	m_arrBoardSelf(NULL),
	m_nColumn(10), m_nRow(10),
	m_nHeight(20), m_nWidth(20),
	m_selfRemain(20), m_enemyRemain(20)
{

}

CGameBoard::~CGameBoard(void)
{
	DeleteBoard();
}

void CGameBoard::SetupEnemy(void) {
	if (m_arrBoard == NULL)
		CreateBoard();
	int placeCol, placeRow;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			m_arrBoard[i][j] = 0;
	bool horizontal = true;  //Определение положения корабля относительно плоскости (вертикальное или горизонтальное)
	//Определение положения 4-палубного корабля
	srand(time(0));
	horizontal = (int)rand() % 2 * horizontal;
	placeCol = (int)rand() % 10;
	placeRow = (int)rand() % 10;
	if(horizontal && placeCol + 3 > 9)
		placeCol -= placeCol + 3 - 9;
	if(!horizontal && placeRow + 3 > 9)
		placeRow -= placeRow + 3 - 9;
	if(horizontal)
		for (int i = placeCol; i <= placeCol + 3; i++)
			m_arrBoard[placeRow][i] = 1;
	else 
		for (int i = placeRow; i <= placeRow + 3; i++)
			m_arrBoard[i][placeCol] = 1;
	//Определение положений 3-палубных кораблей
	int k = 2;
	while (k > 0) {
		horizontal = (int)rand() % 2 * true;
		placeCol = (int)rand() % 10;
		placeRow = (int)rand() % 10;
		if (horizontal && placeCol >= 8)
			continue;
		if (!horizontal && placeRow >= 8)
			continue;
		if (m_arrBoard[placeRow][placeCol] != 0)
			continue;
		if (horizontal) {
			if (placeCol - 1 >= 0) {
				if (m_arrBoard[placeRow][placeCol - 1] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoard[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoard[placeRow + 1][placeCol - 1] != 0)
						continue;
			}
			if (placeCol + 3 < 10) {
				if (m_arrBoard[placeRow][placeCol + 3] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoard[placeRow - 1][placeCol + 3] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoard[placeRow + 1][placeCol + 3] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeCol; i < placeCol + 3; i++) {
				if (m_arrBoard[placeRow][i] != 0) {
					flag = false;
					break;
				}
				if (placeRow - 1 >= 0)
					if (m_arrBoard[placeRow - 1][i] != 0) {
						flag = false;
						break;
					}
				if (placeRow + 1 < 10)
					if (m_arrBoard[placeRow + 1][i] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		else {
			if (placeRow - 1 >= 0) {
				if (m_arrBoard[placeRow - 1][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoard[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoard[placeRow - 1][placeCol + 1] != 0)
						continue;
			}
			if (placeRow + 3 < 10) {
				if (m_arrBoard[placeRow + 3][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoard[placeRow + 3][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoard[placeRow + 3][placeCol + 1] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeRow; i < placeRow + 3; i++) {
				if (m_arrBoard[i][placeCol] != 0) {
					flag = false;
					break;
				}
				if (placeCol - 1 >= 0)
					if (m_arrBoard[i][placeCol - 1] != 0) {
						flag = false;
						break;
					}
				if (placeCol + 1 < 10)
					if (m_arrBoard[i][placeCol + 1] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		if (horizontal) {
			for (int i = placeCol; i < placeCol + 3; i++)
				m_arrBoard[placeRow][i] = 1;
			k--;
		}
		else {
			for (int i = placeRow; i < placeRow + 3; i++)
				m_arrBoard[i][placeCol] = 1;
			k--;
		}
	}
	//Определение положений 2-палубных кораблей
	k = 3;
	while (k > 0) {
		horizontal = (int)rand() % 2 * true;
		placeCol = (int)rand() % 10;
		placeRow = (int)rand() % 10;
		if (horizontal && placeCol >= 9)
			continue;
		if (!horizontal && placeRow >= 9)
			continue;
		if (m_arrBoard[placeRow][placeCol] != 0)
			continue;
		if (horizontal) {
			if (placeCol - 1 >= 0) {
				if (m_arrBoard[placeRow][placeCol - 1] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoard[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoard[placeRow + 1][placeCol - 1] != 0)
						continue;
			}
			if (placeCol + 2 < 10) {
				if (m_arrBoard[placeRow][placeCol + 2] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoard[placeRow - 1][placeCol + 2] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoard[placeRow + 1][placeCol + 2] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeCol; i < placeCol + 2; i++) {
				if (m_arrBoard[placeRow][i] != 0) {
					flag = false;
					break;
				}
				if (placeRow - 1 >= 0)
					if (m_arrBoard[placeRow - 1][i] != 0) {
						flag = false;
						break;
					}
				if (placeRow + 1 < 10)
					if (m_arrBoard[placeRow + 1][i] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		else {
			if (placeRow - 1 >= 0) {
				if (m_arrBoard[placeRow - 1][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoard[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoard[placeRow - 1][placeCol + 1] != 0)
						continue;
			}
			if (placeRow + 2 < 10) {
				if (m_arrBoard[placeRow + 2][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoard[placeRow + 2][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoard[placeRow + 2][placeCol + 1] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeRow; i < placeRow + 2; i++) {
				if (m_arrBoard[i][placeCol] != 0) {
					flag = false;
					break;
				}
				if (placeCol - 1 >= 0) 
					if (m_arrBoard[i][placeCol - 1] != 0) {
						flag = false;
						break;
					}
				if (placeCol + 1 < 10)
					if (m_arrBoard[i][placeCol + 1] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		if (horizontal) {
			for (int i = placeCol; i < placeCol + 2; i++)
				m_arrBoard[placeRow][i] = 1;
			k--;
		}
		else {
			for (int i = placeRow; i < placeRow + 2; i++)
				m_arrBoard[i][placeCol] = 1;
			k--;
		}
	}
	//Определение положений 1-палубных кораблей
	k = 4;
	while (k > 0) {
		placeCol = (int)rand() % 10;
		placeRow = (int)rand() % 10;
		if (m_arrBoard[placeRow][placeCol] == 0) {
			if (placeCol - 1 >= 0)
				if (m_arrBoard[placeRow][placeCol - 1] != 0)
					continue;
			if (placeCol + 1 < 10)
				if (m_arrBoard[placeRow][placeCol + 1] != 0)
					continue;
			if (placeRow - 1 >= 0)
				if (m_arrBoard[placeRow - 1][placeCol] != 0)
					continue;
			if (placeRow + 1 < 10)
				if (m_arrBoard[placeRow + 1][placeCol] != 0)
					continue;
			if (placeCol - 1 >= 0 && placeRow - 1 >= 0)
				if (m_arrBoard[placeRow - 1][placeCol - 1] != 0)
					continue;
			if (placeCol + 1 < 10 && placeRow - 1 >= 0)
				if (m_arrBoard[placeRow - 1][placeCol + 1] != 0)
					continue;
			if (placeCol - 1 >= 0 && placeRow + 1 < 10)
				if (m_arrBoard[placeRow + 1][placeCol - 1] != 0)
					continue;
			if (placeCol + 1 < 10 && placeRow + 1 < 10)
				if (m_arrBoard[placeRow + 1][placeCol + 1] != 0)
					continue;
			m_arrBoard[placeRow][placeCol] = 1;
			k--;
		}
	}
}
//Функция аналогична функции `SetupEnemy` только для поля игрока
void CGameBoard::SetupSelf(void) {
	if (m_arrBoardSelf == NULL)
		CreateBoardSelf();
	int placeCol, placeRow;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			m_arrBoardSelf[i][j] = 0;
	bool horizontal = true;
	horizontal = (int)rand() % 2 * horizontal;
	placeCol = (int)rand() % 10;
	placeRow = (int)rand() % 10;
	if (horizontal && placeCol + 3 > 9)
		placeCol -= placeCol + 3 - 9;
	if (!horizontal && placeRow + 3 > 9)
		placeRow -= placeRow + 3 - 9;
	if (horizontal)
		for (int i = placeCol; i <= placeCol + 3; i++)
			m_arrBoardSelf[placeRow][i] = 1;
	else
		for (int i = placeRow; i <= placeRow + 3; i++)
			m_arrBoardSelf[i][placeCol] = 1;

	int k = 2;
	while (k > 0) {
		horizontal = (int)rand() % 2 * true;
		placeCol = (int)rand() % 10;
		placeRow = (int)rand() % 10;
		if (horizontal && placeCol >= 8)
			continue;
		if (!horizontal && placeRow >= 8)
			continue;
		if (m_arrBoardSelf[placeRow][placeCol] != 0)
			continue;
		if (horizontal) {
			if (placeCol - 1 >= 0) {
				if (m_arrBoardSelf[placeRow][placeCol - 1] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoardSelf[placeRow + 1][placeCol - 1] != 0)
						continue;
			}
			if (placeCol + 3 < 10) {
				if (m_arrBoardSelf[placeRow][placeCol + 3] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][placeCol + 3] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoardSelf[placeRow + 1][placeCol + 3] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeCol; i < placeCol + 3; i++) {
				if (m_arrBoardSelf[placeRow][i] != 0) {
					flag = false;
					break;
				}
				if (placeRow - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][i] != 0) {
						flag = false;
						break;
					}
				if (placeRow + 1 < 10)
					if (m_arrBoardSelf[placeRow + 1][i] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		else {
			if (placeRow - 1 >= 0) {
				if (m_arrBoardSelf[placeRow - 1][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoardSelf[placeRow - 1][placeCol + 1] != 0)
						continue;
			}
			if (placeRow + 3 < 10) {
				if (m_arrBoardSelf[placeRow + 3][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoardSelf[placeRow + 3][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoardSelf[placeRow + 3][placeCol + 1] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeRow; i < placeRow + 3; i++) {
				if (m_arrBoardSelf[i][placeCol] != 0) {
					flag = false;
					break;
				}
				if (placeCol - 1 >= 0)
					if (m_arrBoardSelf[i][placeCol - 1] != 0) {
						flag = false;
						break;
					}
				if (placeCol + 1 < 10)
					if (m_arrBoardSelf[i][placeCol + 1] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		if (horizontal) {
			for (int i = placeCol; i < placeCol + 3; i++)
				m_arrBoardSelf[placeRow][i] = 1;
			k--;
		}
		else {
			for (int i = placeRow; i < placeRow + 3; i++)
				m_arrBoardSelf[i][placeCol] = 1;
			k--;
		}
	}

	k = 3;
	while (k > 0) {
		horizontal = (int)rand() % 2 * true;
		placeCol = (int)rand() % 10;
		placeRow = (int)rand() % 10;
		if (horizontal && placeCol >= 9)
			continue;
		if (!horizontal && placeRow >= 9)
			continue;
		if (m_arrBoardSelf[placeRow][placeCol] != 0)
			continue;
		if (horizontal) {
			if (placeCol - 1 >= 0) {
				if (m_arrBoardSelf[placeRow][placeCol - 1] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoardSelf[placeRow + 1][placeCol - 1] != 0)
						continue;
			}
			if (placeCol + 2 < 10) {
				if (m_arrBoardSelf[placeRow][placeCol + 2] != 0)
					continue;
				if (placeRow - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][placeCol + 2] != 0)
						continue;
				if (placeRow + 1 < 10)
					if (m_arrBoardSelf[placeRow + 1][placeCol + 2] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeCol; i < placeCol + 2; i++) {
				if (m_arrBoardSelf[placeRow][i] != 0) {
					flag = false;
					break;
				}
				if (placeRow - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][i] != 0) {
						flag = false;
						break;
					}
				if (placeRow + 1 < 10)
					if (m_arrBoardSelf[placeRow + 1][i] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		else {
			if (placeRow - 1 >= 0) {
				if (m_arrBoardSelf[placeRow - 1][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoardSelf[placeRow - 1][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoardSelf[placeRow - 1][placeCol + 1] != 0)
						continue;
			}
			if (placeRow + 2 < 10) {
				if (m_arrBoardSelf[placeRow + 2][placeCol] != 0)
					continue;
				if (placeCol - 1 >= 0)
					if (m_arrBoardSelf[placeRow + 2][placeCol - 1] != 0)
						continue;
				if (placeCol + 1 < 10)
					if (m_arrBoardSelf[placeRow + 2][placeCol + 1] != 0)
						continue;
			}
			bool flag = true;
			for (int i = placeRow; i < placeRow + 2; i++) {
				if (m_arrBoardSelf[i][placeCol] != 0) {
					flag = false;
					break;
				}
				if (placeCol - 1 >= 0)
					if (m_arrBoardSelf[i][placeCol - 1] != 0) {
						flag = false;
						break;
					}
				if (placeCol + 1 < 10)
					if (m_arrBoardSelf[i][placeCol + 1] != 0) {
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;
		}
		if (horizontal) {
			for (int i = placeCol; i < placeCol + 2; i++)
				m_arrBoardSelf[placeRow][i] = 1;
			k--;
		}
		else {
			for (int i = placeRow; i < placeRow + 2; i++)
				m_arrBoardSelf[i][placeCol] = 1;
			k--;
		}
	}

	k = 4;
	while (k > 0) {
		placeCol = (int)rand() % 10;
		placeRow = (int)rand() % 10;
		if (m_arrBoardSelf[placeRow][placeCol] == 0) {
			if (placeCol - 1 >= 0)
				if (m_arrBoardSelf[placeRow][placeCol - 1] != 0)
					continue;
			if (placeCol + 1 < 10)
				if (m_arrBoardSelf[placeRow][placeCol + 1] != 0)
					continue;
			if (placeRow - 1 >= 0)
				if (m_arrBoardSelf[placeRow - 1][placeCol] != 0)
					continue;
			if (placeRow + 1 < 10)
				if (m_arrBoardSelf[placeRow + 1][placeCol] != 0)
					continue;
			if (placeCol - 1 >= 0 && placeRow - 1 >= 0)
				if (m_arrBoardSelf[placeRow - 1][placeCol - 1] != 0)
					continue;
			if (placeCol + 1 < 10 && placeRow - 1 >= 0)
				if (m_arrBoardSelf[placeRow - 1][placeCol + 1] != 0)
					continue;
			if (placeCol - 1 >= 0 && placeRow + 1 < 10)
				if (m_arrBoardSelf[placeRow + 1][placeCol - 1] != 0)
					continue;
			if (placeCol + 1 < 10 && placeRow + 1 < 10)
				if (m_arrBoardSelf[placeRow + 1][placeCol + 1] != 0)
					continue;
			m_arrBoardSelf[placeRow][placeCol] = 1;
			k--;
		}
	}

}

void CGameBoard::CreateBoard(void) {
	if (m_arrBoard != NULL)
		DeleteBoard();
	m_arrBoard = new int* [m_nRow];
	for (int i = 0; i < m_nRow; i++) {
		m_arrBoard[i] = new int[m_nColumn];
		for (int j = 0; j < m_nColumn; j++) {
			m_arrBoard[i][j] = 0;
		}
	}
}

void CGameBoard::CreateBoardSelf(void) {
	if (m_arrBoardSelf != NULL)
		DeleteBoardSelf();
	m_arrBoardSelf = new int* [m_nRow];
	for (int i = 0; i < m_nRow; i++) {
		m_arrBoardSelf[i] = new int[m_nColumn];
		for (int j = 0; j < m_nColumn; j++) {
			m_arrBoardSelf[i][j] = 0;
		}
	}
}

int CGameBoard::GetBoardSpace(int row, int col) {
	if (row < 0 || row >= m_nRow || col < 0 || col >= m_nColumn)
		return 0;
	return m_arrBoard[row][col];
}

int CGameBoard::GetBoardSelfSpace(int row, int col) {
	if (row < 0 || row >= m_nRow || col < 0 || col >= m_nColumn)
		return 0;
	return m_arrBoardSelf[row][col];
}

void CGameBoard::DeleteBoard(void)
{
	if (m_arrBoard != NULL)
	{
		for (int i = 0; i < m_nRow; i++)
		{
			if (m_arrBoard[i] != NULL)
			{
				delete[] m_arrBoard[i];
				m_arrBoard[i] = NULL;
			}
		}
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

void CGameBoard::DeleteBoardSelf(void)
{
	if (m_arrBoardSelf != NULL)
	{
		for (int i = 0; i < m_nRow; i++)
		{
			if (m_arrBoardSelf[i] != NULL)
			{
				delete[] m_arrBoardSelf[i];
				m_arrBoardSelf[i] = NULL;
			}
		}
		delete[] m_arrBoardSelf;
		m_arrBoardSelf = NULL;
	}
}

void CGameBoard::SetBoardSpace(int row, int col, int value) {
	m_arrBoard[row][col] = value;
}

void CGameBoard::SetBoardSelfSpace(int row, int col, int value) {
	m_arrBoardSelf[row][col] = value;
}

void CGameBoard::SelfDecrease(void) {
	m_selfRemain--;
}

void CGameBoard::EnemyDecrease(void) {
	m_enemyRemain--;
}

int CGameBoard::DefineWinner(void) {
	if (m_selfRemain == 0)
		return -1;  //Поражение игрока
	else if (m_enemyRemain == 0)
		return 1;  //Победа Игрока
	else return 0;  //Игра продолжается
}

void CGameBoard::RepaintDeadEnemy(int row, int col) {
	int i = row, j = col;
	while (i < 10 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		if (m_arrBoard[i][j] != 3)
			return;
		i++;
	}
	i = row;
	while (i >= 0 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		if (m_arrBoard[i][j] != 3)
			return;
		i--;
	}
	i = row;
	while (j < 10 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		if (m_arrBoard[i][j] != 3)
			return;
		j++;
	}
	j = col;
	while (j >= 0 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		if (m_arrBoard[i][j] != 3)
			return;
		j--;
	}
	j = col;
	//Перекрашивание
	while (i < 10 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		m_arrBoard[i][j] = 4;
		i++;
	}
	i = row;
	while (i >= 0 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		m_arrBoard[i][j] = 4;
		i--;
	}
	i = row;
	while (j < 10 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		m_arrBoard[i][j] = 4;
		j++;
	}
	j = col;
	while (j >= 0 && m_arrBoard[i][j] != 0 && m_arrBoard[i][j] != 2) {
		m_arrBoard[i][j] = 4;
		j--;
	}
}

void CGameBoard::RepaintDeadSelf(int row, int col) {
	int i = row, j = col;
	while (i < 10 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		if (m_arrBoardSelf[i][j] != 3)
			return;
		i++;
	}
	i = row;
	while (i >= 0 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		if (m_arrBoardSelf[i][j] != 3)
			return;
		i--;
	}
	i = row;
	while (j < 10 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		if (m_arrBoardSelf[i][j] != 3)
			return;
		j++;
	}
	j = col;
	while (j >= 0 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		if (m_arrBoardSelf[i][j] != 3)
			return;
		j--;
	}
	j = col;
	//Перекрашивание
	while (i < 10 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		m_arrBoardSelf[i][j] = 4;
		i++;
	}
	i = row;
	while (i >= 0 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		m_arrBoardSelf[i][j] = 4;
		i--;
	}
	i = row;
	while (j < 10 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		m_arrBoardSelf[i][j] = 4;
		j++;
	}
	j = col;
	while (j >= 0 && m_arrBoardSelf[i][j] != 0 && m_arrBoardSelf[i][j] != 2) {
		m_arrBoardSelf[i][j] = 4;
		j--;
	}
}

bool CGameBoard::EnemyMove(void) {
	bool flag = false;
	int i, j, row, col;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (m_arrBoardSelf[i][j] == 3) {
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}
	if (!flag) {
		srand(time(0));
		row = rand() % 10;
		col = rand() % 10;
		//Выбор случайной незанятой ячейки стоит ограничить, так как при сильной забитости поля, поиск такой ячейки может занимать много времени
		for (int k = 0; k < 10 && (m_arrBoardSelf[row][col] == 4 || m_arrBoardSelf[row][col] == 2 || m_arrBoardSelf[row][col] == 3); k++) {
			row = rand() % 10;
			col = rand() % 10;
		}
		if (m_arrBoardSelf[row][col] == 4 || m_arrBoardSelf[row][col] == 2 || m_arrBoardSelf[row][col] == 3) {
			for (i = 0; i < 10; i++) {
				for (j = 0; j < 10; j++) {
					if (m_arrBoardSelf[row][col] != 4 && m_arrBoardSelf[row][col] != 2 && m_arrBoardSelf[row][col] != 3)
						break;
				}
			}
		}
		if (m_arrBoardSelf[row][col] == 0) {
			m_arrBoardSelf[row][col] = 2;
			return false;
		}
		else if (m_arrBoardSelf[row][col] == 1) {
			m_arrBoardSelf[row][col] = 3;
			RepaintDeadSelf(row, col);
			return true;
		}
	}
	//Обработка хода при наличии попадания
	else {
		row = i;
		col = j;
		if (col - 1 >= 0 && m_arrBoardSelf[row][col - 1] != 2) {
			if (m_arrBoardSelf[row][col - 1] == 0) {
				m_arrBoardSelf[row][col - 1] = 2;
				return false;
			}
			else if (m_arrBoardSelf[row][col - 1] == 1) {
				m_arrBoardSelf[row][col - 1] = 3;
				RepaintDeadSelf(row, col - 1);
				return true;
			}
		}
		else if (row - 1 >= 0 && m_arrBoardSelf[row - 1][col] != 2) {
			if (m_arrBoardSelf[row - 1][col] == 0) {
				m_arrBoardSelf[row - 1][col] = 2;
				return false;
			}
			else if (m_arrBoardSelf[row - 1][col] == 1) {
				m_arrBoardSelf[row - 1][col] = 3;
				RepaintDeadSelf(row - 1, col);
				return true;
			}
		}
		if (col + 1 < 10 && m_arrBoardSelf[row][col + 1] != 2 && m_arrBoardSelf[row][col + 1] != 3) {
			if (m_arrBoardSelf[row][col + 1] == 0) {
				m_arrBoardSelf[row][col + 1] = 2;
				return false;
			}
			else if (m_arrBoardSelf[row][col + 1] == 1) {
				m_arrBoardSelf[row][col + 1] = 3;
				RepaintDeadSelf(row, col + 1);
				return true;
			}
		}
		else if (col + 1 < 10 && m_arrBoardSelf[row][col + 1] == 3) {
			col++;
			while (col < 10 && m_arrBoardSelf[row][col] == 3)
				col++;
			if (col < 10) {
				if (m_arrBoardSelf[row][col] == 1) {
					m_arrBoardSelf[row][col] = 3;
					RepaintDeadSelf(row, col);
					return true;
				}
				else {
					m_arrBoardSelf[row][col] = 2;
					return false;
				}
			}
		}
		else if (row + 1 < 10 && m_arrBoardSelf[row + 1][col] != 2 && m_arrBoardSelf[row + 1][col] != 3) {
			if (m_arrBoardSelf[row + 1][col] == 0) {
				m_arrBoardSelf[row + 1][col] = 2;
				return false;
			}
			else if (m_arrBoardSelf[row + 1][col] == 1) {
				m_arrBoardSelf[row + 1][col] = 3;
				RepaintDeadSelf(row + 1, col);
				return true;
			}
		}
		else if (row + 1 < 10 && m_arrBoardSelf[row + 1][col] == 3) {
			row++;
			while (row < 10 && m_arrBoardSelf[row][col] == 3)
				row++;
			if (row < 10) {
				if (m_arrBoardSelf[row][col] == 1) {
					m_arrBoardSelf[row][col] = 3;
					RepaintDeadSelf(row, col);
					return true;
				}
				else {
					m_arrBoardSelf[row][col] = 2;
					return false;
				}
			}
		}
	}
	return false;
}

void CGameBoard::SetSelfRemain(int x) {
	m_selfRemain = x;
}

void CGameBoard::SetEnemyReamin(int x) {
	m_enemyRemain = x;
}