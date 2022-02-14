#pragma once
class CGameBoard
{
public:
	CGameBoard(void); //�����������

	~CGameBoard(void); //����������

	void SetupEnemy(void); //������� ����������� �������� ���������

	void SetupSelf(void); // ������� ����������� ����������� ��������

	int GetWidth(void) const { return m_nWidth; }  //������ ��������� ������ ������
	int GetHeight(void) const { return m_nHeight; }  //������� ��������� ������ ������
	int GetColumn(void) const { return m_nColumn; }  //������� ��������� ������� �������
	int GetRow(void) const { return m_nRow; }  //������� ��������� ������� ������

	void DeleteBoard(void);  //������� �������� �������� ���� ���������
	void DeleteBoardSelf(void);  //������� �������� �������� ���� ������
	int GetBoardSpace(int row, int col); //������� ��������� �������� �� �������� ������ ���� ���������
	int GetBoardSelfSpace(int row, int col);  //������� ��������� �������� �� �������� ������ ���� ������
	void SetBoardSpace(int row, int col, int value);  //������� ��������� ��������� �������� � �������������� ������ ���� ���������
	void SetBoardSelfSpace(int row, int col, int value);  //������� ��������� ��������� �������� � �������������� ������ ���� ������
	void SelfDecrease(void);  //���������� ���������� ������ �������� �� 1 � ������
	void EnemyDecrease(void);  //���������� ���������� ������ �������� �� 1 � ���������
	int DefineWinner(void);  //������� ����������� ����������
	void RepaintDeadEnemy(int row, int col);  //������� ����������� ������� � ���������, ���� �� ��� ���������
	void RepaintDeadSelf(int row, int col);  //������� ����������� ������� � ������, ���� �� ��� ���������
	bool EnemyMove(void);  //�������, ����������� ��� ���������
	void SetEnemyReamin(int x);  //������� ��������� ���������� ���������� �������� � ���������
	void SetSelfRemain(int x);  //������� ��������� ���������� ���������� �������� � ������

	
private:
	void CreateBoard(void);  //������� �������� �������� ���� ���������
	void CreateBoardSelf(void);  //������� �������� �������� ���� ������
	int** m_arrBoard;       //������ ���������� ����
	int** m_arrBoardSelf;   //������ ���� ������

	int m_nWidth;  //������ ������
	int m_nHeight;  //������ ������
	int m_nColumn;  //������ �������
	int m_nRow;  //������ ������
	int m_selfRemain;  //������� ���������� ������ �������� ������
	int m_enemyRemain;  //������� ���������� ������ �������� ���������
};

