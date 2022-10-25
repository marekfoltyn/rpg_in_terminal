/** \file LiveObj.cpp
 *  Implementation of CLiveObj class.
 *  \author Marek Foltýn <foltyma1@fit.cvut.cz> */
 
#include "CLiveObj.hpp"

using namespace std;

CLiveObj::CLiveObj(const string name, int id, int health, int attack, char design, CMap * map)
	: CObj(name, id, design) {
	srand (time(NULL));
	c_health = health;
	c_attack = attack;
	c_direction = 1;
	c_map = map;
}

int CLiveObj::Health() const {
	return c_health;
}
int CLiveObj::Attack() const {
	return c_attack;
}

int CLiveObj::Direction() const {
	return c_direction;
}

void CLiveObj::setDirection(int direction){
	c_direction = direction;
}

int CLiveObj::Move(int direction){
	// get new x,y
	int nx=0;
	int ny=0;
	switch(direction){
		case DIRECTION_UP:
			nx = c_x;
			ny = c_y-1;
		break;
		case DIRECTION_RIGHT:
			nx = c_x+1;
			ny = c_y;
		break;
		case DIRECTION_DOWN:
			nx = c_x;
			ny = c_y+1;
		break;
		case DIRECTION_LEFT:
			nx = c_x-1;
			ny = c_y;
		break;
	}
	// change direction
	c_direction = direction;
	// check if there is a free place (if not, return id of this place)
	if( (*c_map)[nx][ny] != 0){
		return (*c_map)[nx][ny];
	}
	// move
	(*c_map)[nx][ny] = c_id;
	(*c_map)[c_x][c_y] = 0;
	c_x = nx;
	c_y = ny;
	return 0;
}

void CLiveObj::InFrontOf(int & x, int & y, int direction) const {
	switch(direction){
		case DIRECTION_UP: x=c_x; y=c_y-1; break;
		case DIRECTION_RIGHT: x=c_x+1; y=c_y; break;
		case DIRECTION_DOWN: x=c_x; y=c_y+1; break;
		case DIRECTION_LEFT: x=c_x-1; y=c_y; break;
	}
} 

int CLiveObj::Hit(int attack){
	int realAttack;
	// reduce attack
	for(int i=4; i>=1; i--){
		realAttack = rand()%(attack+1); 
		if( realAttack >= attack-(attack/i) ){
			break;
		}
	}
	c_health -= realAttack;
	
	if(c_health < 0){
		int ret = c_health+realAttack;
		c_health=0;
		return ret;
	} else {
		return realAttack;
	}
}

