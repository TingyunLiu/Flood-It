#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(int n) : View(n) {
	// allocate memory for theDisplay (2D array)
	theDisplay = new char*[gridSize];
	for (int i = 0; i < gridSize; ++i) {
		theDisplay[i] = new char[gridSize];
		for(int j = 0; j < gridSize; ++j){
			theDisplay[i][j] = '0';
		} // inner for
	} // outer for
}

TextDisplay::~TextDisplay() {
	for (int i = 0; i < gridSize; ++i) {
		delete [] theDisplay[i];
	} // for
	delete [] theDisplay;
}

void TextDisplay::notify(int row, int column, char ch) {
	theDisplay[row][column] = ch;
}

void TextDisplay::print(ostream &out) const {
	for (int i = 0; i < gridSize; ++i) {
		for (int j = 0; j < gridSize; ++j) {
			out << theDisplay[i][j];
		} // inner for
		out << endl;
	} // outer for
}
