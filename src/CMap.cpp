/** \file CMap.cpp
 * Implementation of CMap class.
 * \author Marek Foltýn <foltyma1@fit.cvut.cz> */
 
#include "CMap.hpp"

using namespace std;

CMap::CMap(const string url){
	// Load map from file
	string line;
	ifstream fin(url.c_str());
	if( fin.fail() || fin.bad() ){
		endwin();
		cerr<<"Input file not opened."<<endl;
		exit(1);
	}
	getline(fin,line);
	c_width = line.size()-1; // skip newline ('\n')
	fin.clear() ;
	fin.seekg(0, ios::beg) ;
	c_map.resize(c_width);
	// loading line per line - all rows must have THE SAME width!!
	while( getline( fin, line) ){
		if( line.size()-1 != c_width){
			endwin();
			cerr<<"Bad map file format"<<endl;
			exit(1);
		}
		for(unsigned i=0; i<line.size()-1; i++){
			if(line[i] == '#'){
				c_map[i].push_back((int)ID_WALL);
			} else if(line[i] == '.') {
				c_map[i].push_back((int)ID_BLOCKED);
			} else {
				c_map[i].push_back((int)ID_FREE);
			}
		}
	}
	fin.close();
	c_heigth = c_map[0].size();
}

CMap::~CMap(){
	map<int, CObj*>::iterator iter;
	for (iter = c_obj.begin(); iter != c_obj.end(); iter++) {
		delete iter->second;
	}
}

vector<int> & CMap::operator [] (int x) {
	return c_map[x];
}

unsigned CMap::getHeight() const {
	return c_heigth;
}

unsigned CMap::getWidth() const{
	return c_width;
}

void CMap::addCObj( CObj * obj ){
	int x,y,id;
	obj->Position(x,y);
	id = obj->Id();
	c_map[x][y] = id;
	c_obj[id] = obj;
}
void CMap::delCObj( CObj * obj ){
	int x,y,id;
	obj->Position(x,y);
	id = obj->Id();
	c_map[x][y] = 0;
	c_obj.erase(id);
}

void CMap::findFreePlace(int & x, int & y) const {
	int newX=0;
	int newY=0;
	while( c_map[newX][newY] != 0 ){
		newX = rand()%c_width;
		newY = rand()%c_heigth;
	}
	x=newX;
	y=newY;
}

void CMap::setPlayerXY(int x, int y){
	c_player_x = x;
	c_player_y = y;
}

void CMap::getPlayerXY(int & x, int & y) const {
	x=c_player_x;
	y=c_player_y;
}

CObj * CMap::getObj(int id){
	return c_obj[id];
}

