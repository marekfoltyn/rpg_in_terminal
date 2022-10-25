/** \file CGame.hpp
 * Header for CGame class
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */


#ifndef __CGAME__
#define __CGAME__

#include <dirent.h>
#include <stdio.h>
#include <time.h>

#include <cstring>
#include <sstream>

#include "CPlayer.hpp"
#include "CCreature.hpp"
#include "CItem.hpp"
#include "CMap.hpp"

using namespace std;

/// Game engine class
/** This class represent all the engine of the game. 
 * It loads the files, starts the games and controls the game cycle.
 */
class CGame{
	public:
		/// Constructor
		/** Starts the engine, loads ncurses. */
		CGame();
		/// Destructor
		/** Exit ncurses, free map from memory */
		~CGame();
		/// Main menu
		/** Shows the main menu.
		 * \return Selected option: MENU_CONTINUE, MENU_NEW_GAME or MENU_EXIT */
		int showMainMenu() const;
		/// Prepare for running game cycle
		/** Deletes previous game data, runs map selection, role editor and loads necessary data */
		void newGame();
		/// Game cycle
		/** Runs main game loop - get input, update states and draw screen */
		void runCycle();
		/// Menu option constant.
		static const int MENU_CONTINUE=0;
		/// Menu option constant.
		static const int MENU_NEW_GAME=1;
		/// Menu option constant.
		static const int MENU_EXIT=3;
	private:
		/// Adress of a folder with .map files
		static const string MAP_FOLDER;
		/// Address of an item list file
		static const string ITEMS_FILE;
		/// Address of an creature list file
		static const string CREATURES_FILE;
		/// How many nanoseconds will the game sleep before next cycle 
		static const int SLEEP_TIME=10000;

		/// If true, there is a started game
		bool enableContinue;
		CMap * c_map;
		CPlayer * c_player;
		/// list of creatures in map
		vector<CCreature *> c_creatures;
		/// event list
		string c_events[6];
		/// creature structure - used for loading from file
		struct creature_prototype{
			int level_begin, level_end, health_max, attack_max;
			string name;
			char design;
		};
		/// item structure - used for loading from file
		struct item_prototype{
			int one_use,level_begin, level_end, health, attack, experience;
			string name;
			char design;
		};
		/// list of prototypes - for generating new creatures in map
		map<int, vector<creature_prototype> > c_creature_prototypes;
		/// list of prototypes - for generating new creatures in map
		map<int, vector<item_prototype> > c_item_prototypes;
		/// active item slot (0-5) - for drawing selected
		int d_activeItem;
		/// number of killed creatures (shown on gameover)
		int c_creatures_killed;
		/// Role selection menu - player selects the character and his skill points
		void roleEditor();
		/// Map selection - player selects a map from map folder
		void mapSelection();
		/// Preparation for new game and placing objects
		void prepareNewGame();
		/// Generates an unique ID for new object
		/** \param item if true, it generates ID for an item, otherwise for a creature
		 *  \return an ID */
		int generateID(bool item=false);
		/// Generates an unique ID for player
		/** \return an ID */
		int generatePlayerID();
		/// Updates player stats, dependent on pressed key
		/** \param input Key code of pressed key */
		void updatePlayerStats(int input);
		/// Updates creatures stats
		void updateAIStats();
		/// Generates new items and creatures and places them into map
		/** Generation depends on multiple factors: generation count, items list and creatures list */
		void generateItemsAndCreatures();
		/// Generates a creature. Depends on player level
		/** \return CCreature pointer */
		CCreature * generateCreature();
		/// Generates a item. Depends on player level
		/** \return CItem pointer */
		CItem * generateItem();
		/// Adds new event
		/** \param event Text of the event */
		void addEvent(std::string event);
		/// Shows screen with game controls
		void drawControls() const;
		/// Draws game screen (map, HUD, objects, ...)
		void drawScreen();
		/// Shows gameover screen
		void showGameOver();
		/// Stops program sleeps for nanoseconds
		/** \param us Nanoseconds to sleep */
		void sleep(long us);
};

#endif // __CGAME__
