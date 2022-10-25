/** \file CPlayer.hpp
 * Header for CPlayer class
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */


#ifndef __CPLAYER__
#define __CPLAYER__

#include <math.h>

#include "CLiveObj.hpp"
#include "CItem.hpp"
 
using namespace std;

/// player-controlled object in map
/** This class allows to control the player figure. It can do all the necessary things (move, attack, take/drop/use an item, level up, ...)
 */
class CPlayer : public CLiveObj{
	private:
		int c_level;
		int c_percentage;
		int c_prevLvlExp;
		int c_experience;
		int c_expSpeed;
		int c_maxHealth;
		vector<CItem *> c_items;
	public:
		/// Constructor
		/** Creates an instance of player (map-dependent)
		 * \param name Name of player (role - for example Wizard, Elf, Palladin, ...)
		 * \param id Unique id
		 * \param health Maximum health
		 * \param attack Maximum attack
		 * \param expSpeed Speed of gaining experience (percentually)
		 * \param center Char-design
		 * \param map CMap pointer to map
		 */
		CPlayer(const string name, int id, int health, int attack, int expSpeed, char center, CMap * map);
		/// Destructor. Deletes the player and even the items player holding.
		~CPlayer();
		/// Gets the design (direction-dependent)
		/** \return Char-design of the player */
		virtual char Design() const;
		/// Gets the level of the player
		/** \return Actual level of the player */
		int Level() const;
		/// Gets the item in selected slot
		/** \param id ID of the slot (0-5)
		 *  \return CItem pointer of the item
		 */
		CItem * Item(int id) const;
		/// Adds an item to player's selected slot
		/** \param slot ID of player's slot (0-5)
		 *  \param item CItem pointer of the item
		 */
		void AddItem(int slot, CItem * item);
		/// Deletes the item from player
		/** \param slot ID of player's slot (0-5) */
		void DelItem(int slot);
		/// Uses the item
		/** \param slot ID of player's slot (0-5) */
		void UseItem(int slot);
		/// Finds a free item slot
		/** \param active ID of active slot (0-5) - it tries to find the nearest free slot
		 * \return ID of found slot, -1 if all the slots are full */
		int FindFreeSlot(int active) const;
		/// Finds a full item slot
		/** \param active ID of active slot (0-5) - it tries to find the nearest full slot
		 * \return ID of found slot, -1 if all the slots are empty */
		int FindFullSlot(int active) const;
		/// Return maximum health player can reach
		/** \return Maximum health */
		int MaxHealth() const;
		/// Adds health to player
		/** \param amount Health amount to be added */
		void AddHealth(int amount);
		/// Adds attack to player
		/** \param amount Attack amount to be added */
		void AddAttack(int amount);
		/// Adds experience to player
		/** \param amount Experience amount to be added */
		void AddExp (int amount);
		/// Gets how many percent of experience to next level player reached
		/** \return percent of experience gained to next level */
		int Percentage() const;
};

#endif // __CPLAYER__

