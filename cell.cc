#include "cell.h"
#include "game.h"
using namespace std;

void Cell::notifyNeighbours() const {
	for (int i = 0; i < numNeighbours; ++i) {
		if (neighbours[i]->getState()-'0' == prevState) {
			neighbours[i]->notify(state, prevState);
		} // if
	} // for
}

void Cell::notifyGame() const {
	game->notify(row, column, prevState, state);
}

Cell::Cell() : state(0), prevState(0), numNeighbours(0) { }

char Cell::getState() const { return state+'0'; }
 
void Cell::setState(const int& change) {
	state = change;
}

void Cell::setCoords(const int row, const int column) { 
	this->row = row;
	this->column = column;
}

void Cell::setGame(Game * game) {
	this->game = game;
}

void Cell::addNeighbour(Cell *neighbour) {
	neighbours[numNeighbours] = neighbour;
	++numNeighbours;
}

  /*
   * The following methods are provided as a hint towards 
   * implementing the notification.
   * You should try to use the methods with the given signatures.
   *
   * If you feel the need to change the *signature* of the method 
   * (do not change the name) you may do so but MUST provide a comprehensive 
   * explanation in your code why you felt the change was necessary
   */
	
	
  /*
   * Intended to be called only by the game class for changing the state of the 0 0 cell
   */
void Cell::notify(const int & change) {
	prevState = state;
	setState(change);
	notifyGame();
	notifyNeighbours();
}
// TWO NOTIFY DO THE SAME THING
	/*
	 * Intended to be called by Cells to notify their neighbors
	 * current: this cells current(new) state 
	 * previous: this cells past state
	 */
void Cell::notify(const int & current, const int & previous) {
	prevState = state;
	setState(current);
	notifyGame();
	notifyNeighbours();
}

