/** \file main.cpp
 *  Implementation of class CObj
 *  \author Marek Foltýn <foltyma1@fit.cvut.cz> */

#include "CObj.hpp"

using namespace std;

CObj::CObj(string name, int id, char design){
	c_name = name;
	c_id = id;
	c_design = design;
}

void CObj::Position(int & x, int & y) const {
	x = c_x;
	y = c_y;
}

int CObj::Id() const {
	return c_id;
}

void CObj::setPosition(int x, int y){
	c_x = x;
	c_y = y;
}

string CObj::Name() const {
	return c_name;
}

char CObj::Design() const {
	return c_design;
}
