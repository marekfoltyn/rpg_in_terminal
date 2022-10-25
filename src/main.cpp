/** \file main.cpp
 *  Main file, that starts the CGame class.
 *  \author Marek Foltýn <foltyma1@fit.cvut.cz> */

/** \mainpage
 *  Documentation of a semestral project "RPG game".
 * 	Class overview:
 *  \image html inherit_graph_0.png
 *  \image html inherit_graph_1.png
 *  \image html inherit_graph_2.png
 *  \image html inherit_graph_3.png
 *  \image html inherit_graph_4.png
 *  Dependency overview:
 *  \image html main_8cpp__incl.png
 */

#include "CGame.hpp"

using namespace std;

int main(void){
	CGame game;
	int choice;
	while((choice = game.showMainMenu()) != game.MENU_EXIT){
		if(choice == game.MENU_CONTINUE){
			game.runCycle();
		}
		if(choice == game.MENU_NEW_GAME){
			game.newGame();
			game.runCycle();
		}
	}
}
