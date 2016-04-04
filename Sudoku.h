#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>

class Sudoku {
<<<<<<< HEAD
=======

>>>>>>> 25307b6c9b8374ee3669868e2c77916a52a0c57a
public:
	Sudoku();
	Sudoku(const int init_map[]);
	void setMap(const int set_map[]);
	int getElement(int index);
	void setElement(int index,int value);
	int getFirstZeroIndex();
	bool isCorrect();
<<<<<<< HEAD
	void printOut();
=======
	void printOut(bool n);
>>>>>>> 25307b6c9b8374ee3669868e2c77916a52a0c57a
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
