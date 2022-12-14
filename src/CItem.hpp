/** \file CItem.hpp
 * Header for CItem class
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */

#ifndef __CITEM__
#define __CITEM__

#include "CObj.hpp"

using namespace std;

/// An item (player can take it)
/** This class represents an item in the game. Player can take it.
 *  The item has also an effect on player - permanent or just once.
 */
class CItem : public CObj{
	protected:
		/// The item adds this amount of health to the player
		int c_health;
		/// The item adds this amount of attack to the player
		int c_attack;
		/// The item adds this amount of experience to the player
		int c_exp;
		/// If true, the item can be used only one time, otherwise card has permanent effect (for example sword)
		bool c_usable;
	public:
		/// Constructor. Makes the item with desired abilities.
		/** Constructor. Makes the item with desired abilities.
		 * \param name Name of the item
		 * \param id Unique ID of the item (generated by game engine)
		 * \param design Design-char of the item
		 * \param health The item adds this amount of health to the player
		 * \param attack The item adds this amount of attack to the player
		 * \param exp The item adds this amount of experience to the player
		 * \param usable If true, the item can be used only one time, otherwise card has permanent effect (for example sword)
		 */
		CItem(const string name, int id, const char design, int health, int attack, int exp, bool usable);
		/// Get the amount of health which this item gives to player
		/** \return The amount of health which this item gives to player */
		int Health() const;
		/// Get the amount of attack which this item gives to player
		/** \return The amount of attack which this item gives to player */
		int Attack() const;
		/// Get the amount of experience which this item gives to player
		/** \return The amount of experience which this item gives to player */
		int Exp() const;
		/// Check if this item is permanent or for one use
		/** \return True, if the item is for one use, false for permanent */
		bool Usable() const;
};


#endif // __CITEM__
