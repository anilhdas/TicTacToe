#include <iostream>
#include <windows.h>

using namespace std;

char player = 'X';
char matrix[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

HANDLE OutStdConsole;

char pastInput[9];
int pastInputIndex = 0;

int turnsSoFar = 0;
short gameStatus = 0;

const WORD COLOR_WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD COLOR_TITLE = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD COLOR_PLAYER_X = FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD COLOR_PLAYER_Y = FOREGROUND_BLUE | FOREGROUND_GREEN;
const WORD COLOR_WARNING = FOREGROUND_RED | FOREGROUND_GREEN;

void Draw()
{
	system("cls");

	SetConsoleTextAttribute(OutStdConsole, COLOR_TITLE);
	cout << endl << " ! < < Tic Tac Toe > > !" << endl << endl << endl;
	SetConsoleTextAttribute(OutStdConsole, COLOR_WHITE);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(matrix[i][j] == 'X')
				SetConsoleTextAttribute(OutStdConsole, COLOR_PLAYER_X);
			else if(matrix[i][j] == 'O')
				SetConsoleTextAttribute(OutStdConsole, COLOR_PLAYER_Y);

			cout << "   " << matrix[i][j];
			SetConsoleTextAttribute(OutStdConsole, COLOR_WHITE);
		}
		cout << endl << endl;
	}
}

bool ValidateInput(char currentInput)
{
	for (int i = 0; i < pastInputIndex; i++)
	{
		if (pastInput[i] == currentInput)
			return false;
	}

	pastInput[pastInputIndex++] = currentInput;
	return true;
}

void SwitchPlayer()
{
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
}

void Tick(char input)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (matrix[i][j] == input)
			{
				matrix[i][j] = player;
				break;
			}
		}
		cout << endl;
	}
}

bool Win()
{
	// 0 -> No Win
	// 1 -> Player X Win
	// 2 -> Player O Win
	gameStatus = 0;

	for (int i = 0; i < 3; i++)
	{
		if ((matrix[i][0] == 'X' && matrix[i][1] == 'X' && matrix[i][2] == 'X') ||
			(matrix[0][i] == 'X' && matrix[1][i] == 'X' && matrix[2][i] == 'X'))
			gameStatus = 1;
		else if ((matrix[i][0] == 'O' && matrix[i][1] == 'O' && matrix[i][2] == 'O') ||
			(matrix[0][i] == 'O' && matrix[1][i] == 'O' && matrix[2][i] == 'O'))
			gameStatus = 2;
	}

	if (gameStatus == 0)
	{
		if ((matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X') ||
			(matrix[2][0] == 'X') && matrix[1][1] == 'X' && matrix[0][2] == 'X')
			gameStatus = 1;
		else if ((matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O') ||
			(matrix[2][0] == 'O') && matrix[1][1] == 'O' && matrix[0][2] == 'O')
			gameStatus = 2;
	}

	return gameStatus > 0;
}

void Input()
{
	char a;
	cout << "Player ";

	if(player == 'X')
		SetConsoleTextAttribute(OutStdConsole, COLOR_PLAYER_X);
	else
		SetConsoleTextAttribute(OutStdConsole, COLOR_PLAYER_Y);

	cout << player << endl << endl;
	SetConsoleTextAttribute(OutStdConsole, COLOR_WHITE);

	cout << "Press the number of the field: ";
	cin >> a;

	if (ValidateInput(a))
	{
		Tick(a);
		SwitchPlayer();
		turnsSoFar++;
		return;
	}

	SetConsoleTextAttribute(OutStdConsole, COLOR_WARNING);
	cout << "WARNING:: Please select an empty field!!" << endl << endl;
	SetConsoleTextAttribute(OutStdConsole, COLOR_WHITE);
}

int main()
{
	OutStdConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	Draw();

	while (turnsSoFar < 9) {
		Input();
		Draw();

		if (turnsSoFar >= 5)
			if (Win())
				break;
	}

	if (gameStatus == 1)
	{
		SetConsoleTextAttribute(OutStdConsole, COLOR_PLAYER_X);
		cout << "Player X Win !!" << endl << endl << endl;
	}
	else if (gameStatus == 2)
	{
		SetConsoleTextAttribute(OutStdConsole, COLOR_PLAYER_Y);
		cout << "Player O Win !!" << endl << endl << endl;
	}
	else
	{
		SetConsoleTextAttribute(OutStdConsole, COLOR_WARNING);
		cout << "That was a TIE! Tough one. Try again.." << endl << endl << endl;
	}

	SetConsoleTextAttribute(OutStdConsole, COLOR_WHITE);
	system("pause");

	return 0;
}
