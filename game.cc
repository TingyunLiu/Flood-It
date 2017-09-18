#include "game.h"
using namespace std;

Game::Game() : theGrid(NULL), gridSize(0), existed(false) {
	for (int i = 0; i < 5; ++i) {
		colours[i] = 0;
	} // for
}

Game::~Game() {
	clearGame();
}

void Game::clearGame() {
	for (int i = 0; i < gridSize; ++i) {
		delete [] theGrid[i];
	} // for
	delete [] theGrid;
        // set all colours to 0
	for (int i = 0; i < 5; ++i) {
                colours[i] = 0;
        } // for
}

void Game::notify(int row, int column, unsigned int oldState, unsigned int newState) {
	theGrid[row][column].setState(newState);
	notification->notify(row, column, newState);
	--colours[oldState];
	++colours[newState];
}

bool Game::isWon() const {
	for (int i = 0; i < 5; ++i) {
		if (colours[i] >= (gridSize * gridSize)) return true;
	} // for
	return false;

}

int Game::getSize() {
	return gridSize;
}

void Game::init(int n, GameNotification *gameNotification) {
	notification = gameNotification;
	if (existed) clearGame(); // clear old grid if existed
	existed = true;
	gridSize = n; // set up gridSize
	// allocate memory for theGrid (2d array)
	theGrid = new Cell*[gridSize];
	for (int i = 0; i < gridSize; ++i) {
		theGrid[i] = new Cell[gridSize];
		for (int j = 0; j < gridSize; ++j) {
			theGrid[i][j].setGame(this);
			theGrid[i][j].setCoords(i,j);
		} // inner for
	} // outer for

	// connect each cells from top-left to bottom-right
	for (int i = 0; i < gridSize-1; ++i) {
		for (int j = 0; j < gridSize-1; ++j) {
			theGrid[i][j].addNeighbour(&theGrid[i+1][j]);
			theGrid[i][j].addNeighbour(&theGrid[i][j+1]);
		} // inner for 
	} // outer for
	// connect each cells from bottom-right to top-left
	for (int i = gridSize-1; i > 0; --i) {
		for (int j = gridSize-1; j > 0; --j) {
			theGrid[i][j].addNeighbour(&theGrid[i-1][j]);
			theGrid[i][j].addNeighbour(&theGrid[i][j-1]);
		} // inner for
	} // outer for
	// connect edges
	for (int i = 0; i < gridSize-1; ++i) {
		theGrid[i][gridSize-1].addNeighbour(&theGrid[i+1][gridSize-1]);
		theGrid[gridSize-1][i].addNeighbour(&theGrid[gridSize-1][i+1]);
	} // for
	for (int i = gridSize-1; i > 0; --i) {
		theGrid[i][0].addNeighbour(&theGrid[i-1][0]);
		theGrid[0][i].addNeighbour(&theGrid[0][i-1]);
	} // for
	// set the number of 0 to be gridSize * gridSize
	colours[0] = gridSize * gridSize;
}

void Game::change(const int &state) {
	if (state+'0' == theGrid[0][0].getState()) return;
	theGrid[0][0].notify(state);
}

void Game::init(int row, int column, int state) {
	// update state if it it valid coordinates
	if (row >= 0 && row < getSize() && column >= 0 &&
        column < getSize() && state >= 0 && state <= 4) {
		char old = theGrid[row][column].getState();
		theGrid[row][column].setState(state);
		--colours[old-'0'];
		++colours[state];
	}// if
}

