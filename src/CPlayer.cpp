/** \file CPlayer.cpp
 * Implementation of CPlayer class
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */
 
#include "CPlayer.hpp"
 
using namespace std;

CPlayer::CPlayer(const string name, int id, int health, int attack, int expSpeed, char center, CMap * map)
	: CLiveObj(name, id, health, attack, center, map){
	c_level = 1;
	c_percentage = 0;
	c_prevLvlExp = 0;
	c_experience = 0;  
	c_expSpeed = expSpeed;
	c_items.resize(6,NULL);
	c_maxHealth = health;
}

CPlayer::~CPlayer(){
	for(int i=0; i<(int)c_items.size(); i++){
		if(c_items[i] != NULL) delete c_items[i];
	}
}

char CPlayer::Design() const {
	if(c_direction==0) return '^';
	if(c_direction==1) return '>';
	if(c_direction==2) return 'v';
	if(c_direction==3) return '<';
	return '?';
}

void CPlayer::AddItem(int slot, CItem * item){
	c_items[slot] = item;
	// update stats
	c_attack += item->Attack();
}

void CPlayer::DelItem(int slot){
	// update stats
	c_attack -= c_items[slot]->Attack();
	c_items[slot] = NULL;
}

void CPlayer::UseItem(int slot){
	CItem * item = c_items[slot];
	AddHealth(item->Health());
	AddExp( item->Exp() );
	DelItem(slot);
	delete item;
}

int CPlayer::FindFreeSlot(int active) const {
	// searching from actual
	int slot=active;
	for(int i=0; i<6; i++){
		if(c_items[slot] == NULL){
			return slot;
		}
		slot++;
		if(slot==6) slot=0;
	}
	return -1;
}

int CPlayer::FindFullSlot(int active) const{
	// searching from actual
	int slot=active;
	for(int i=0; i<6; i++){
		if(c_items[slot] != NULL){
			return slot;
		}
		slot++;
		if(slot==6) slot=0;
	}
	return -1;
}

void CPlayer::AddHealth(int amount){
	c_health += amount;
	if(c_health > c_maxHealth ){
		c_health = c_maxHealth;
	}
}

void CPlayer::AddExp (int amount){
	c_experience += (amount*c_expSpeed)/100.0;
	int nextLevel = c_prevLvlExp + (pow(3,c_level-1)/pow(2,c_level-1))*500;
	if( c_experience >= nextLevel ){
		c_level++;
		c_prevLvlExp = nextLevel;
		nextLevel = c_prevLvlExp + (pow(3,c_level-1)/pow(2,c_level-1))*500;
		// regenerate and add attack
		c_maxHealth *= 1.1;
		AddHealth(c_maxHealth/4);
		c_attack++;
	}
	c_percentage = ((double)(c_experience-c_prevLvlExp)/(nextLevel-c_prevLvlExp))*100;
}

int CPlayer::Level() const {
	return c_level;
}

CItem * CPlayer::Item(int id) const {
	return c_items[id];
}

int CPlayer::MaxHealth() const{
	return c_maxHealth;
}

void CPlayer::AddAttack(int amount){
	c_attack+=amount;
}

int CPlayer::Percentage() const {
	return c_percentage;
}
