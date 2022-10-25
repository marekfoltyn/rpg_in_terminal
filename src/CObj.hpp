/** \file CObj.hpp
 *  Header for CObj class.
 *  \author Marek Foltýn <foltyma1@fit.cvut.cz> */

#ifndef __COBJ__
#define __COBJ__

#include <string>

using namespace std;

/// Basic item class
/** This class represents an object that can be put into a map.
 *  It stores coordinates, name and look of the object. 
 */
class CObj{
	protected:
		/// name of the object
		string c_name;
		/// char-design
		char c_design;
		/// unique id 
		int c_id;
		/// x-axis coordinate
		int c_x;
		/// y-axis coordinate
		int c_y;
	public:
		/// Maximal ID of an item
		static const int MAX_ID_ITEM=10000;
		/// Maximal ID of a creature (higher is only ID of player)
		static const int MAX_ID_CREATURE=1000000;
		/// Constructor
		/** Makes a new object (map-independent).
		 * \param name Name of the object
		 * \param id Unique ID of the object
		 * \param design Char design of the object
		 */
		CObj(string name, int id, char design);
		/// Destructor.
		virtual ~CObj(){};
		/// Gets the position
		/** Stores the position to x and y
		 * \param Stores the "x" position here.
		 * \param Stores the "y" position here.
		 */
		void Position(int & x, int & y) const;
		/// Gets the ID
		/** \return ID of the object */
		int Id() const;
		/// Sets the position of the object
		/* Sets the position (map-independent)
		 * \param Position of x-axis
		 * \param Position of y-axis
		 */
		void setPosition(int x, int y);
		/// Gets the name
		/** \return The name of the object */
		string Name() const;
		/// Gets the design of the object
		/** \return Char which represents the design of the object. */
		virtual char Design() const;
};

#endif // __COBJ__
