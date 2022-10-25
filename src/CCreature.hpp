/** \file CCreature.hpp
 * Header for CCreature class
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */

#ifndef __CCREATURE__
#define __CCREATURE__

#include <math.h>

#include "CLiveObj.hpp"
 
using namespace std;

/// A creature
/** This class represents computer-controlled creature. It can decide what to do (stay, move, attack).
 */
class CCreature : public CLiveObj{
	private:
		/// Search for player next to this creature
		/** \return If there is a player, returns direction, where he is, otherwise -1 */
		int findAttackablePlayer() const;
		/// Computes the direction vector of the player
		/** \param x x-coordinate of the vector will be saved here
		    \param y y-coordinate of the vector will be saved here */
		void findPlayerVector(int & x, int & y) const;
	public:
		/// Constructor
		/** Makes a creature (map-dependent!)
		 * \param name Name of the creature
		 * \param id Unique ID
		 * \param health Amount of health
		 * \param maxAttack Maximum of attack
		 * \param design Char-design
		 * \map map CMap pointer of a map
		 */
		CCreature(const string name, int id, int health, int maxAttack, char design, CMap * map);
		/// AI behaviour. Returns number of action, what it would do (but it doesn't do it - it does game engine)
		/** \return -1 (do nothing), 0-3 (move with this direction), 4-7 (attack with this direction -4) */
		int AI();
};

#endif // __CCREATURE__

