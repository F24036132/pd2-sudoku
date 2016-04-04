#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>

class Sudoku {
public:
	Sudoku();
	Sudoku(const int init_map[]);
	void setMap(const int set_map[]);
	int getElement(int index);
	void setElement(int index,int value);
	int getFirstZeroIndex();
	bool isCorrect();
	void printOut(bool n);
	static const int sudokuSize=81;
	static const int sudokuNum=9;
	
	void giveQuestion();
	void readIn();
	void solve();
	void changeNum(int a,int b);
	void changeRow(int a,int b);
	void changeCol(int a,int b);
	void rotate(int n);
	void flip(int n);
	void transform();

private:
	bool checkUnity(int arr[]);
	void possibleElement();
	bool solution();
	int map[sudokuSize];
	int element[sudokuSize][sudokuNum];
};
