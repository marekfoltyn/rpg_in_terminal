/** \file CItem.cpp
 * Implementation of CItem class.
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */

#include "CItem.hpp"

using namespace std;

CItem::CItem(const string name, int id, const char design, int health, int attack, int exp, bool usable)
	: CObj(name, id, design) {
	c_health = health;
	c_attack = attack;
	c_exp = exp;
	c_usable = usable;
}

int CItem::Health() const {
	return c_health;
}

int CItem::Attack() const {
	return c_attack;
}

int CItem::Exp() const {
	return c_exp;
}

bool CItem::Usable() const {
	return c_usable;
}
