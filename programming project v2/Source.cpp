#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;

int ** maze; 
bool** wasHere;
bool** correctPath; 
vector<int>CozumMatrisX;
vector<int>CozumMatrisY;

int startX, startY; 
int endX, endY;     

bool Exit_from_program = 0;
bool cozumVarmi;

int width;
int height;

void generateRandomMaze(int row , int column) {
	maze = new int*[row];
	for (int i = 0; i < row; i++)
		maze[i] = new int[column];

	int prob;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++) {
			prob = rand() % 15;
			if(prob<=2)
			    maze[i][j] = 1;
			else
				maze[i][j] = 0;
		}
	maze[0][0] = 0;
	maze[row - 1][column - 1] = 0;
}

bool recursiveSolve(int x, int y) {

	if (x == endX && y == endY && maze[x][y] == 0) { correctPath[x][y] = true; return true; } 
	if (maze[x][y] == 1 || wasHere[x][y]) return false;
	
	wasHere[x][y] = true;
	if (x != 0) { 
		if (recursiveSolve(x - 1, y)) { 
			correctPath[x][y] = true; 
			CozumMatrisX.push_back(x);
			CozumMatrisY.push_back(y);
			return true;
		}
	}

	if (x != width - 1) { 
		if (recursiveSolve(x + 1, y)) { 
			correctPath[x][y] = true;
			CozumMatrisX.push_back(x);
			CozumMatrisY.push_back(y);
			return true;
		}
	}

	if (y != 0) { 
		if (recursiveSolve(x, y - 1)) { 
			correctPath[x][y] = true;
			CozumMatrisX.push_back(x);
			CozumMatrisY.push_back(y);
			return true;
		}
	}

	if (y != height - 1) { 
		if (recursiveSolve(x, y + 1)) { 
			correctPath[x][y] = true;
			CozumMatrisX.push_back(x);
			CozumMatrisY.push_back(y);
			return true;
		}
	}

	return false;
}

void solveMaze(int row_count,int col_count) {

	for (int row = 0; row < row_count; row++) {
		for (int col = 0; col < col_count; col++) {
			wasHere[row][col] = false;
			correctPath[row][col] = false;
		}
	}
	cozumVarmi = recursiveSolve(startX, startY);
	
	if (cozumVarmi == false)
		cout << "No solution" << endl;
}

void printMaze(int rowSize, int columnSize) {
	cout << endl;
	cout << "+--------+" << endl
		<< "| MATRIX |" << endl
		<< "+--------+" << endl;

	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			cout << maze[i][j]<< " ";
		}
		cout << endl;
	}
}

void printResultPath(int rowSize, int columnSize) {
	cout << endl<<endl;
	cout << "+---------------+" << endl
	    << "| RESULT MATRIX |" << endl
		<< "+---------------+" << endl;

	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			if (correctPath[i][j] == true)
				cout << 0;
			else
				cout << '-';
			cout << " ";
		}
		cout << endl;
	}
	cout << endl<<endl;

	int x = 0, y = 0;
	cout << "+-------------+" << endl
	     << "| RESULT PATH |" << endl
    	 << "+-------------+" << endl
	     << "X" << "  Y" <<endl;

	if (cozumVarmi) {
		for (int i = 0; i < CozumMatrisX.size(); i++) {
			cout <<CozumMatrisX[CozumMatrisX.size() - i - 1] << "  " << CozumMatrisY[CozumMatrisY.size() - i - 1] << endl;
		}
		cout <<rowSize - 1 << "  " << columnSize - 1 << endl;
	}
}

void menu() {
	int array[10][10] = { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		                  1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
	                 	  1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
						  1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
						  1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		                  1, 0, 0, 1, 1, 0, 0, 0, 1, 1,
		                  1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
		                  1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
		                  1, 1, 1, 0, 0, 1, 1, 0, 0, 1,
		                  1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
								                    	};

	int choice;
	cout << "1 - Solve given maze" << endl
		 << "2 - Solve a randomized maze" << endl
		 << "3 - Exit" << endl;
	cin >> choice;

	if (choice == 1) {
		int row_count = sizeof(array) / sizeof array[0];
		int col_count = sizeof array[0] / sizeof(int);

		maze = new int*[row_count];
		for (int i = 0; i < row_count; i++)
			maze[i] = new int[col_count];

		wasHere = new bool*[row_count];
		for (int i = 0; i < row_count; i++)
			wasHere[i] = new bool[col_count];

		correctPath = new bool*[row_count];
		for (int i = 0; i < row_count; i++)
			correctPath[i] = new bool[col_count];

		for (int i = 0; i < row_count; i++)
			for (int j = 0; j < col_count; j++)
				maze[i][j] = array[i][j];

		printMaze(row_count, col_count);

		startX = 0; startY = 0;
		endX = row_count - 1;  endY = col_count - 1;
		width = col_count;  height = row_count;

		solveMaze(row_count, col_count);
		printResultPath(row_count, col_count);
		system("pause");
	}

	else if (choice == 2) {
		int row, column;
		cout << "Enter the number of rows" << endl;
		cin >> row;
		cout << "Enter the number of columns" << endl;
		cin >> column;

		generateRandomMaze(row,column);
		printMaze(row, column);

		wasHere = new bool*[row];
		for (int i = 0; i < row; i++)
			wasHere[i] = new bool[column];

		correctPath = new bool*[row];
		for (int i = 0; i < row; i++)
			correctPath[i] = new bool[column];

		startX = 0; startY = 0;
		endX = row - 1;  endY = column - 1;
		width = row;  height = column;

		solveMaze(row, column);
		printResultPath(row, column);
		system("pause");
	}

	else if (choice == 3) { Exit_from_program = 1; }

	else {
		cout << "Please Select a valid choice" << endl;
		system("pause");
	}

	CozumMatrisX.clear();
	CozumMatrisY.clear();
}

int main() {
	while (Exit_from_program==0) {
		menu();
		system("cls");
	}
}
