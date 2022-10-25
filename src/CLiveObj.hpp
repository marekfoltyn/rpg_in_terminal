/** \file LiveObj.hpp
 *  Header for CLiveObj class.
 *  \author Marek Foltýn <foltyma1@fit.cvut.cz> */

#ifndef __CLIVEOBJ__
#define __CLIVEOBJ__

#include "CMap.hpp"
#include "CObj.hpp"

using namespace std;

/// Live object in map
/** This class represents live objects in map (player, creatures). 
 *  They can move, have health, direction and attack.
 */
class CLiveObj : public CObj{
	protected:
		/// Health points of the live object
		int c_health;
		/// Attack points
		int c_attack;
		/// direction of the object - 0 up, 1 right, 2 down, 3 left
		int c_direction; 
		/// pointer to map
		CMap * c_map;
	public:
		/// Direction constant.
		static const int DIRECTION_UP=0;
		/// Direction constant.
		static const int DIRECTION_RIGHT=1;
		/// Direction constant.
		static const int DIRECTION_DOWN=2;
		/// Direction constant.
		static const int DIRECTION_LEFT=3;
		
		/// Constuctor
		/** Makes a new live object (map-dependent!)
		 * \param name Just name.
		 * \param id Unique ID
		 * \param health Amount of health
		 * \param attack Maximum attack
		 * \param design Char design
		 * \param map Pointer to CMap (necessary for move in map)
		 */
		CLiveObj(const string name, int id, int health, int attack, char design, CMap * map);
		/// Gets the health
		/** \return Amount of health left */
		int Health() const;
		/// Gets the attack
		/** \return Amount of attack */
		int Attack() const;
		/// Gets the direction
		/** \return Direction of the object (DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT) */
		int Direction() const;
		/// Sets the direction
		/** \param direction  Direction of the object (DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT) */
		void setDirection(int direction);
		/// Attack on this object
		/** Someone attack this object
		 * \param attack Amount of attack
		 * \return amount of health destroyed
		 */
		int Hit(int attack);
		/// Move a live object
		/** Go to desired direction. If there is not a free place, object will not move
		 * \param direction Direction of move (DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT)
		 * \return ID of the object on desired place
		 */
		virtual int Move(int direction);
		/// Gets coords in front of a player/creature
		/** When we can look, what is around the player (we can swicth the direction withou moving the object)
		 * \param x Here will be saved x-axis coordinate
		 * \param y Here will be saved y-axis coordinate
		 * \param direction Direction of object (0 up, 1 right, 2 down, 3 left)
		 */
		void InFrontOf(int & x, int & y, int direction) const; 
};

#endif // __CLIVEOBJ__

