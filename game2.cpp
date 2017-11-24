#include <iostream>
#include <cstdlib>
using namespace std;

#define MAXSIDE 25
#define MAXMINES 100
int SIDE , MINES;
char col[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n'};


void initBoard(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE])
{
	for (int i = 0; i < SIDE; i++)
		for (int j = 0; j < SIDE; ++j)
			myBoard[i][j] = realBoard[i][j]='_';
return;
}


void placeMines(char realBoard[][MAXSIDE], int minesPlace[][2])
{
	for (int i = 0; i < MINES; i++)
	{
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		minesPlace[i][0] = x;
		minesPlace[i][1] = y;

		realBoard[x][y] = 'B';		
	}
return;
}



void printBoard(char myBoard[][MAXSIDE])
{
	cout<<endl<<"\t\t\t  ";
	for (int i = 0; i < SIDE; i++)
		// cout<<col[i]<<" ";
		cout<<i<<" ";
	cout<<endl;

	for (int i=0; i<SIDE; i++)
	{
		cout<<"\t\t\t"<<i<<" ";

		for (int j=0; j<SIDE; j++)
			cout<<myBoard[i][j]<<" ";
		cout<<endl;
	}
return;
}


bool isValidMove(int x, int y)
{
	return ((x >= 0) && (x < SIDE) &&	
			(y >= 0) && (y < SIDE));
}


void makeMove(int &x ,int &y)
{
	char col;
	int numCol;
	while(1)
	{
		cout<<endl<<"\nEnter your move (Row, Col) -> ";
		// cin>>x>>col;
		cin>>x>>numCol;
		// y = col-'a';
		// if(isValidMove(y,x))
		y=numCol;
		if(isValidMove(x,numCol))
			break;
		else
			cout<<endl<<"\n** Incorrect move ** \n";
	}
return;
}



bool isMine (int row, int col, char board[][MAXSIDE])
{
	return (board[row][col] == 'B');
}


int adjMines(int row, int col, int minesPlace[][2],
					 char realBoard[][MAXSIDE])
{
	int count=0;
	if( isValidMove(row-1, col) && isMine(row-1, col, realBoard) ||
		isValidMove(row+1, col) && isMine(row+1, col, realBoard) ||
		isValidMove(row-1, col+1) && isMine(row-1, col+1, realBoard) ||
		isValidMove(row+1, col-1) && isMine(row+1, col-1, realBoard) ||
		isValidMove(row-1, col+1) && isMine(row-1, col+1, realBoard) ||
		isValidMove(row+1, col-1) && isMine(row+1, col-1, realBoard) ||
		isValidMove(row, col-1) && isMine(row, col-1, realBoard) ||
		isValidMove(row, col+1) && isMine(row, col+1, realBoard) )
			count++;

	return count;
}





bool gameOverUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
			int minesPlace[][2], int row, int col, int &movesLeft)
{
	if (myBoard[row][col] != '_')
		return false;		

	if(isMine(row, col, realBoard))
	{
		for (int i = 0; i < MINES; i++)
			myBoard[minesPlace[i][0]][minesPlace[i][1]]='B';
		myBoard[row][col] = 'X';
		printBoard(myBoard);
		cout<<"\n <<  you LOST  >> " <<endl;
		return true;
	}

	else
	{
		movesLeft--;
		int countAdjMines = adjMines(row, col, minesPlace, realBoard);
		myBoard[row][col] = countAdjMines + '0';

		if(countAdjMines==0)
		{
		if( isValidMove(row-1, col) && !isMine(row-1, col, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row-1, col, movesLeft);

		if( isValidMove(row+1, col) && !isMine(row+1, col, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row+1, col, movesLeft);

		if( isValidMove(row-1, col+1) && !isMine(row-1, col+1, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row-1, col+1, movesLeft);

		if( isValidMove(row+1, col-1) && !isMine(row+1, col-1, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row+1, col-1, movesLeft);

		if( isValidMove(row-1, col+1) && !isMine(row-1, col+1, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row-1, col+1, movesLeft);

		if( isValidMove(row+1, col-1) && !isMine(row+1, col-1, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row+1, col-1, movesLeft);

		if( isValidMove(row, col-1) && !isMine(row, col-1, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row, col-1, movesLeft);

		if( isValidMove(row, col+1) && !isMine(row, col+1, realBoard) )
			gameOverUtil(myBoard, realBoard, minesPlace, row, col+1, movesLeft);
		}

		return false;
	}
}


void chooseLevel ()
{
	int level=0;

	cout<<"Enter the Difficulty Level\n";
	cout<<"Press 0 for BEGINNER (8 * 8 Cells and 10 Mines)\n";
	cout<<"Press 1 for INTERMEDIATE (16 * 16 Cells and 40 Mines)\n";
	cout<<"Press 2 for ADVANCED (24 * 24 Cells and 99 Mines)\n";

	cin>>level;

	if (level == 0)
	{
		SIDE = 8;
		MINES = 10;
	}
	else if (level == 1)
	{
		SIDE = 16;
		MINES = 40;
	}
	else if (level == 2)
	{
		SIDE = 24;
		MINES = 99;
	}
	return;
}


void playGame()
{
	chooseLevel();
	bool gameOver = false;
	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];
	initBoard(myBoard, realBoard);

	int movesLeft = SIDE*SIDE - MINES - 1;
	int x, y, minesPlace[MINES][2];

	placeMines(realBoard, minesPlace);
	// printBoard(realBoard);

	while(!gameOver)
	{
		cout<<"\nCheat board "<<endl;
		printBoard(realBoard);
		cout<<"\nCurrent status of board "<<endl;
		printBoard(myBoard);
		makeMove(x, y);

		gameOver = gameOverUtil(myBoard ,realBoard, minesPlace, x, y, movesLeft);

		if(gameOver==false && movesLeft==0)
		{
			cout<<"\n!!  you WON  !!"<<endl;
			gameOver = true;
		}
	}
	return;
}




int main(int argc, char const *argv[])
{
	playGame();
	return 0;
}