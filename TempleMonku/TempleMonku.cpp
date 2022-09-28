#include <string>
#include <iostream>
using namespace std;

const int sizeX = 10;
const int sizeY = 5;
const char heal = 'X', bomb = 'O';

const int health = 10;
const int damageBomb = 15;

bool endGame = false;
int life = 100;

int exitX = 2, exitY = 10;
int cursorX = 0;
int cursorY = 0;

short templeTemplate[sizeY][sizeX] = 
{
	//0 = nothing
	//1 = health
	//2 = bomb
	//5 = exit
	{0,2,0,2,1,2,2,0,1,2},
	{2,2,0,1,2,1,1,2,2,0},
	{2,1,2,2,2,2,1,2,2,0},
	{0,1,0,2,1,2,2,0,1,2},
	{2,1,1,0,0,1,0,1,0,1}
};
short templeGame[sizeY][sizeX] = 
{
	{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}
};

char CheckSymbolGame(short _horizontal, short _vertical)
{
	return templeGame[_horizontal][_vertical] == 0 ? ' ' : templeGame[_horizontal][_vertical] == 1 ? heal : bomb;
}

void InsertInGrid(short _horizontal, short _vertical)
{
	templeGame[_vertical][_horizontal] = templeTemplate[_vertical][_horizontal];
}
void CheckAction(short _horizontal, short _vertical)
{
	if (templeGame[_vertical][_horizontal] == 0) cout << "This case contain nothing." << endl;
	else if (templeGame[_vertical][_horizontal] == 1) {
		cout << "This case contain a kit of health." << endl;
		if (life + health < 100)
			life += health;
		else
			life = 100;
	}
	else if (templeGame[_vertical][_horizontal] == 2) {
		cout << "This case contain a bomb." << endl;
		if (life - damageBomb <= 0) {
			life = 0;
			endGame = !endGame;
		}
		else
			life -= damageBomb;
	}
	else if (templeGame[_vertical][_horizontal] == 5) {
		cout << "This case is exit." << endl;
		endGame = !endGame;
	}
	string _lifeBar = "Life [" + to_string(life) + "]";
	cout << _lifeBar << endl;
}
bool IsValidCase(short _vertical, short _horizontal) {
	return templeGame[_vertical][_horizontal] == 0;
}
void ShowInterface()
{
	cout << "====================" << endl;
	string grid = "";
	for (short y = 0; y < sizeY; y++) {
		for (short x = 0; x < sizeX; x++) {
			if (y == exitY && x == exitX)
				grid = grid + " [E] ";
			else
				grid = grid + " [" + ((cursorX == x && cursorY == y) && IsValidCase(y, x) ? '_' : CheckSymbolGame(y, x)) + "] ";
		}
		grid += "\n";
	}
	cout << grid << endl;
	cout << "====================" << endl;
}

void Game()
{
	if (!endGame) {
		//Move cursor
		char _input = ' ';
		bool _valid = false;
		while (!_valid) {
			cout << "Move the cursor(z,q,s,d): ";
			cin >> _input;
			_valid = true;
		}
		_valid = false;
		if (_input == 'z')
			cursorY = (cursorY - 1) > 0 ? cursorY - 1 : cursorY;
		else if (_input == 'q')
			cursorX = (cursorX - 1) > 0 ? cursorX - 1 : cursorX;
		else if (_input == 's')
			cursorY = (cursorY + 1) < sizeY ? cursorY + 1 : cursorY;
		else if (_input == 'd')
			cursorX = (cursorX + 1) < sizeX ? cursorX + 1 : cursorX;
		else {
			cout << "Input invalid. Retry." << endl;
			Game();
			return;
		}
		InsertInGrid(cursorX, cursorY);
		system("CLS");
		ShowInterface();
		CheckAction(cursorX, cursorY);
		Game();
	}
	cout << ((life > 0) ? "The game is end. You found the exit." : "You die. Try again :)") << endl;
}
void SetExit(int _horizontal, int _vertical)
{
	if (_horizontal > sizeX)
		exitX = sizeX - 1;
	if (_vertical > sizeY)
		exitY = sizeY - 1;
	templeTemplate[exitY][exitX] = 5;
}
int main()
{
	SetExit(exitX, exitY);
	ShowInterface();
	Game();
}
