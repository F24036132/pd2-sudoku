#include "Sudoku.h"
using namespace std;
int num=0;
int answer[Sudoku::sudokuSize];
int tmpmap[Sudoku::sudokuSize];
int tmpelement[Sudoku::sudokuSize];
int tmpfirst=0;

Sudoku::Sudoku()
{
	for(int i=0;i<sudokuSize;++i)
		map[i]=0;
}

Sudoku::Sudoku(const int init_map[])
{
	for(int i=0;i<sudokuSize;++i)
		map[i]=init_map[i];
}

void Sudoku::setMap(const int set_map[])
{
	for(int i=0;i<sudokuSize;++i)
		map[i]=set_map[i];
}

int Sudoku::getElement(int index)
{
	return map[index];
}

void Sudoku::setElement(int index,int value)
{
	map[index]=value;
}

int Sudoku::getFirstZeroIndex()
{
	for(int i=0;i<sudokuSize;++i)
		if(map[i]==0) return i;
	return -1;
}

bool Sudoku::checkUnity(int arr[])
{
	int arr_unity[9];
	int i;

	for(i=0;i<9;++i)
		arr_unity[i]=0;
	for(i=0;i<9;++i)
		++arr_unity[arr[i]-1];
	for(i=0;i<9;++i)
		if(arr_unity[i]>1)
			return false;
	return true;
}

bool Sudoku::isCorrect()
{
	bool check_result;
	int check_arr[9];
	int i,j,location;

	for(i=0;i<81;i+=9){ // check rows
		for(j=0;j<9;++j)
			check_arr[j]=map[i+j];
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	for(i=0;i<9;++i){ // check columns
		for(j=0;j<9;++j)
			check_arr[j]=map[i+9*j];
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	for(i=0;i<9;++i){ // check cells
		for(j=0;j<9;++j){
			location=27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
			check_arr[j]=map[location];
		}
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	return true;
}

void Sudoku::printOut()
{
	for(int i=0;i<sudokuSize;++i)
		printf("%d%c",map[i],i%9==8?'\n':' ');
}

void Sudoku::possibleElement()
{
	int record[sudokuSize]={0};
	int location,location2,r=1;
	int i,j,k;

	while(r){
		r=0;
		for(i=0;i<sudokuSize;++i){
			for(j=0;j<9;j++)
				element[i][j]=1;
		}
		for(i=0;i<81;i+=9){ // check rows
			for(j=0;j<9;++j){
				for(k=0;k<9;++k)
					if(map[i+k]!=0)
						element[i+j][map[i+k]-1]=0;
			}
		}
		for(i=0;i<9;++i){ // check columns
			for(j=0;j<9;++j){
				for(k=0;k<9;++k)
					if(map[i+9*k]!=0)
						element[i+9*j][map[i+9*k]-1]=0;
			}
		}
		for(i=0;i<9;++i){ // check cells
			for(j=0;j<9;++j){
				location=27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
				for(k=0;k<9;++k){
					location2=27*(i/3)+3*(i%3)+9*(k/3)+(k%3);
					if(map[location2]!=0)
						element[location][map[location2]-1]=0;
				}
			}
		}
		for(i=0;i<sudokuSize;++i){
			if(map[i]==0){
				for(k=0;k<9;++k)
					if(element[i][k]==1)
							record[i]++;
			}
		}
		for(i=0;i<81;++i){
			if(record[i]==1){
				for(j=0;j<9;++j){
					if(element[i][j]==1){
						map[i]=j+1;
						r=1;
						break;
					}
				}
			}
		}
	}
}

bool Sudoku::solution()
{
	int first=getFirstZeroIndex();
	int tmp[sudokuSize];
	int i=0,j;

	for(j=0;j<81;++j)
		answer[j]=map[j];
	do{
		if(i>=9&&first==0) return false;
		if(i>=9){
			map[first]=0;
			if(tmpfirst<=0) first=0;
			else first=tmpmap[--tmpfirst];
			i=tmpelement[first];
		}
		else{
			if(element[first][i]==1){
				map[first]=i+1;
				tmpelement[first]=i;
				if(isCorrect()){
					tmpmap[tmpfirst++]=first;
					first=getFirstZeroIndex();
					i=-1;	   
					if(first==-1) num++;
				}
			}
		}
		i++;
	}while(first>=0&&first<81);
	for(j=0;j<81;++j)
		tmp[j]=map[j];
	for(j=0;j<81;++j)
		map[j]=answer[j];
	first=getFirstZeroIndex();
	i=8;
	do{
		if(i<0){
			map[first]=0;
			if(tmpfirst<=0) first=0;
			else first=tmpmap[--tmpfirst];
			i=tmpelement[first];
		}
		else{
			if(element[first][i]==1){
				map[first]=i+1;
				tmpelement[first]=i;
				if(isCorrect()){
					tmpmap[tmpfirst++]=first;
					first=getFirstZeroIndex();
					i=9;
					if(first==-1){
						j=0;
					   	while(map[j]==tmp[j]&&j!=80)
						   j++;
					   	if(j!=80) num++;
					}
				}
			}
		}
		i--;
	}while(first>=0&&first<81);
	return true;
/*	if(first==-1){
		if(isCorrect()){
			num++;
			for(i=0;i<81;++i)
				answer[i]=map[i];
			return true;
		}
		else return false;
	}
	else{
		for(i=0;i<9;++i){
			if(element[first][i]==1){
				map[first]=i+1;
				if(isCorrect()){
					if(solution()){
						if(num>1) return true;
						else{
							map[first]=0;
							continue;
						}
					}
					else map[first]=0;
				}
				else map[first]=0;
			}
		}
		if(num==1) return true;
		else return false;
	}*/
}

void Sudoku::giveQuestion()
{
	srand(time(NULL));
	int question[sudokuSize]=
		{0,0,2,0,0,3,1,0,5,
		 0,0,0,0,4,0,0,2,0,
		 5,3,0,7,0,0,0,0,0,
		 0,9,7,0,0,0,0,0,8,
		 0,0,0,0,1,0,0,0,0,
		 2,0,0,0,0,0,9,6,0,
		 7,0,0,0,0,6,0,8,4,
		 0,5,0,0,8,0,0,0,0,
		 9,0,0,3,0,0,6,0,0};
	for(int i=0;i<sudokuSize;++i)
		setMap(question);
	transform();
}

void Sudoku::readIn()
{
	int in[sudokuSize];
	for(int i=0;i<sudokuSize;++i){
		cin>>in[i];
		setMap(in);
	}
}

void Sudoku::solve()
{
	if(!isCorrect()) cout<<0<<endl;
	else{
		possibleElement();
		if(getFirstZeroIndex()==-1){
			cout<<1<<endl;
			printOut();
		}
		if(!solution()) cout<<0<<endl;
		else if(num>1) cout<<2<<endl;
		else if(num==1){
			cout<<1<<endl;
			printOut();
		}
	}
}

void Sudoku::changeNum(int a,int b)
{
	if(a==b) return;
	for(int i=0;i<81;i++){
		if(map[i]==a) map[i]=b;
		else if(map[i]==b) map[i]=a;
	}
}

void Sudoku::changeRow(int a,int b)
{
	int tmp[sudokuSize];
	int i,j;

	if(a==b) return;
	for(i=a*27;i<81;++i)
		tmp[i]=map[i];
	for(i=a*27,j=b*27;j<(b+1)*27;++i,++j){
		map[i]=map[j];
		map[j]=tmp[i];
	}
}

void Sudoku::changeCol(int a,int b)
{
	int tmp[81];
	int i,j,k;

	if(a==b) return;
	for(i=a*3;i<81;i+=9){
		for(j=0;j<3;++j)
			tmp[i+j]=map[i+j];
	}
	for(i=a*3,j=b*3;i<81;i+=9,j+=9){
		for(k=0;k<3;++k){
			map[i+k]=map[j+k];
			map[j+k]=tmp[i+k];
		}
	}
}

void Sudoku::rotate(int n)
{
	int tmp[81];
	int i,j,k,l;

	for(i=0;i<81;++i)
		tmp[i]=map[i];
	if(n%4==0) return;
	else if(n%4==1){
		for(i=0,j=8;i<81;i+=9,--j){
			for(k=0,l=0;k<9;++k,l+=9)
				map[j+l]=tmp[i+k];
		}
	}
	else if(n%4==2){
		for(i=0,j=80;i<81;i+=9,j-=9){
			for(k=0;k<9;++k)
				map[j-k]=tmp[i+k];
		}
	}
	else if(n%4==3){
		for(i=0,j=72;i<81;i+=9,++j){
			for(k=0,l=0;k<9;++k,l-=9)
				map[j+l]=tmp[i+k];
		}
	}
}

void Sudoku::flip(int n)
{

	int tmp[81];
	int i,j,k;

	for(i=0;i<81;i++)
		tmp[i]=map[i];
	if(n){
		for(i=0,j=8;i<9;++i,--j)
			for(k=0;k<81;k+=9)
				map[i+k]=tmp[j+k];
	}
	else{
		for(i=0,j=72;i<81;i+=9,j-=9)
			for(k=0;k<9;++k)
				map[i+k]=tmp[j+k];
	}
}

void Sudoku::transform()
{
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	printOut();
}
