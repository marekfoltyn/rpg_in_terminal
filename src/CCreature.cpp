/** \file CCreature.cpp
 * Implementation of CCreature class
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */

#include "CCreature.hpp"
 
using namespace std;

CCreature::CCreature(const string name, int id, int health, int maxAttack, char design, CMap * map)
	: CLiveObj(name, id, health, maxAttack, design, map){}

int CCreature::findAttackablePlayer() const {
	int xmv[] = {0,1,0,-1};
	int ymv[] = {-1,0,1,0};
	for(int i=0; i<4; i++){
		if( (*c_map)[c_x+xmv[i]][c_y+ymv[i]] > MAX_ID_CREATURE){
			return i;
		}
	}
	return -1;
}

void CCreature::findPlayerVector(int & x, int & y) const {
	int _x, _y;
	c_map->getPlayerXY(_x,_y);
	x = _x - c_x;
	y = _y - c_y;
}

int CCreature::AI(){
	// results:
	// -1  do nothing
	// 0-3 move (with this direction)
	// 4-7 attack c_player (with this direction-4)
	int search = findAttackablePlayer();
	if(search != -1){
		// let's attack!
		c_direction = search;
		return 4+search;
	}
	int x,y;
	findPlayerVector(x,y);
	int distance = abs(x) + abs(y);
	if( distance < 20 && rand()%3 != 0){
		// go to player
		int dr;
		// randomly
		if( rand()%2 ){
			dr = (x>0)?1:3; 
		} else {
			dr = (y<0)?0:2;
		}
		
		return dr;
	}
	// Go wherever you want
	if( rand()%3 == 0){
		return rand()%4;
	}
	// Stay
	return -1;
}


