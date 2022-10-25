/** \file CMap.hpp
 *  Header for CMap class.
 *  \author Marek Foltýn <foltyma1@fit.cvut.cz> */


#ifndef __CMAP__
#define __CMAP__

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ncurses.h>

#include "CObj.hpp"

using namespace std;

/// Class which represents 2D map
/** This class represents 2D map. It loads the map from the text file.
 *  It also can store objects CObj.
 */
class CMap{
	private:
		/// data representation of the map
		vector< vector<int> > c_map;
		/// map of objects - key(ID) and value(COBj*)
		map<int,CObj*> c_obj; // id,pointer to object
		/// x-coordinate of player
		int  c_player_x;
		/// y-coordinate of player
		int  c_player_y;
		/// map width
		unsigned c_width;
		/// map height
		unsigned c_heigth;
	public:
		/// id of a free place
		static const int ID_FREE=0;
		/// id of a wall block
		static const int ID_WALL=1;
		/// id of a free place (but not able to go there)
		static const int ID_BLOCKED=-1;
		/// Constructor
		/** Constructor loads a map from a .map text file
		 * \param url URL of a file
		 */
		CMap(const string url);
		/// Destructor
		/** Destructor deletes the map (including the objects in it)
		 */
		~CMap();
		/// Get the id of a selected coordinate
		/** Get the id of a selected coordinate.
		 *  Using: id=map[25][1];
		 * \param x x-axis coordinate of the map
		 */
		vector<int> & operator [](int x);
		/// Get a pointer to this ID
		/** If we have an ID of an object, this function finds the pointer to it
		 * \param id ID of an object
		 * \return CObj pointer of an object
		 */
		CObj * getObj(int id);
		/// Get the width of the map
		/** \return The width of the map */
		unsigned getWidth() const;
		/// Get the height of the map
		/** \return The height of the map */
		unsigned getHeight() const;
		/// Add an object to the map. It places it to the coordinates set in CObj.
		/** \param obj CObj pointer to an object */
		void addCObj( CObj * obj );
		/// Deletes the object from the map (not from memory!)
		/** \param obj CObj pointer to an object */
		void delCObj( CObj * obj );
		/// Generates free coordinates
		/** Randomly gets coordinates of a free place
		 * \param x x-axis coordinate of a found point
		 * \param y y-axis coordinate of a found point
		 */
		void findFreePlace(int & x, int & y) const;
		/// Manipulate with the player in the map
		/** Sets the coordinates of the player
		 * \param x x-axis coordinate of the player
		 * \param y y-axis coordinate of the player
		 */
		void setPlayerXY(int x, int y);
		/// Gets the player's position
		/** Returns the player's position
		 * \param x x-axis coordinate of player will be saved here
		 * \param y y-axis coordinate of player will be saved here
		 */
		void getPlayerXY(int & x, int & y) const;
};

#endif // __CMAP__
