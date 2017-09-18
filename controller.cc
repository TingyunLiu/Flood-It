#include "controller.h"
#include "game.h"
#include "textdisplay.h"
// Uncomment for part (b)
//#include "graphicdisplay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

Controller::Controller(){
  game = new Game();
  td = NULL;
  // TODO - add any code needed for part (b)
}

/*
 * Update the View(s) to indicate the new game state
 */
void Controller::notify(int row, int column, unsigned int state){
  // TODO
  td->notify(row, column, state+'0');
}

/*
 * Called when command init is received
 */
void Controller::init(istream & input, Game & g){
  // TODO
  game = &g;
  int row, column, state;
  while (true) {
    // read in the triple of row column and state
    input >> row >> column;
    // check whether end initialization mode
    if (input.fail() || (row == -1 && column == -1)) break;
    input >> state;
    game->init(row, column, state);
    // check validation of input and call notify TextDisplay if valid
    if (row >= 0 && row < game->getSize() && column >= 0 &&
        column < game->getSize() && state >= 0 && state <= 4) {
    	td->notify(row, column, state+'0');
    } // if
  } // while
}

bool Controller::checkWin(int movesLeft) const {
  if(game->isWon() && movesLeft != 0){
    cout << "Won" << endl;
    return true;
  }
  return false;
}

void Controller::play(){
  srand(time(NULL));
  int moves = 0;
  string cmd;
  while (cin >> cmd) {
    if (cmd == "new") { 
      int gridDimension;
      cin >> gridDimension; 
      game->init(gridDimension, this);
      delete td;
      td = new TextDisplay(gridDimension);
      // Uncomment for part (b)
      // gd = new GraphicDisplay(n);

      moves = 0;
    }
// the ? command is only needed for part (b)
// when graphics command line is enabled
/*   else if (cmd == "?"){
        cout << "White: 0" << endl;
        cout << "Black: 1" << endl;
        cout << "Red:   2" << endl;
        cout << "Green: 3" << endl;
        cout << "Blue:  4" << endl;

   }
*/
    else if (cmd == "init") { //go into initialization mode
      init(cin, *game);
      td->print(cout); //display the board
      if (checkWin(moves)){
        break;
      }
    }
    else if (cmd == "include"){ //initialization from a file
       string file;
       cin >> file;
       ifstream input(file.c_str());
       init(input, *game);
       td->print(cout);
       if (checkWin(moves)){
        break;
      }
    }
    else if (cmd == "switch") { //always switch the (0,0) location
      if (checkWin(moves)){
        break;
      }
      if(moves > 0){
        int next; //get the state we have switched to
        if (cin >> next && (next >= 0 && next <= 4)){
          
          //custom call to method responsible for switching (0,0)
          game->change(next); 

          //print the updated Textdisplay
          td->print(cout);
          --moves;
	       if (moves == 1) {
          cout << moves << " move left" << endl;
	       }
         else {
          cout << moves << " moves left" << endl;
	       }
         if(game->isWon()){
	         cout << "Won" << endl;
	         break;
	       }
 	       if(moves == 0){
  	         cout << "Lost" << endl;
	         break;
	       }
        }
        else cerr << "Invalid move" << endl;
      }
    }
    else if (cmd == "game"){
      cin >> moves;
      if (moves < 0) {
        moves = 0;
      } 
      else if (moves == 1) {
        cout << moves << " move left" << endl;
      }
      else { 
        cout << moves << " moves left" << endl;
      }
      if (checkWin(moves)){
        break;
      }
    }
  }
}

Controller::~Controller(){
// TODO
  delete game;
  delete td;
}
