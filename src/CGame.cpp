
#include "CGame.hpp"

using namespace std;

const string CGame::MAP_FOLDER="src/maps/";
const string CGame::ITEMS_FILE="src/config/itemList.txt";
const string CGame::CREATURES_FILE="src/config/creatureList.txt";

CGame::CGame(){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	srand (time(NULL));	
	c_map = NULL;
	c_player = NULL;
	enableContinue = false;
}

CGame::~CGame(){
	if(c_map != NULL) delete c_map;
	endwin();
}

int CGame::showMainMenu() const {
	clear();
	int cols, rows;
	char key=-1;
	int chosen;
	const char * choices[4];
	
	choices[0] = "Continue";
	choices[1] = "New game";
	choices[2] = "Controls";
	choices[3] = "Exit";
	
	if(enableContinue){
		chosen = 0;
	} else {
		chosen = 1;
	}

	
	// menu cycle
	while(key != 10){ // 10 = enter
		getmaxyx(stdscr,rows,cols);
		
		// recognize arrow keys
		if(key == 3){ // UP
			if(!enableContinue){
				(chosen==1)?chosen=3:chosen--;
			} else {
				(chosen==0)?chosen=3:chosen--;
			}
		}
		if(key == 2){ // DOWN
			if(!enableContinue){
				(chosen==3)?chosen=1:chosen++;
			} else {
				(chosen==3)?chosen=0:chosen++;
			}
		}
		mvaddstr ((rows*0.2), (cols/2)-12,   "#####     ####     ##### ");
		mvaddstr ((rows*0.2)+1, (cols/2)-12, "##  ##    ## ##   ##     ");
		mvaddstr ((rows*0.2)+2, (cols/2)-12, "#####     ####    ## ### ");
		mvaddstr ((rows*0.2)+3, (cols/2)-12, "##  ##    ##      ##   ##");
		mvaddstr ((rows*0.2)+4, (cols/2)-12, "##   ##   ##       ##### ");
		// draw menu
		int i=0;
		if(!enableContinue){
			i=1;
		}
		for(; i<4; i++){
			if(i==chosen){
				attron(A_STANDOUT);
			}
			mvaddstr((rows*0.2)+8+2*i, (cols/2)-(strlen(choices[i])/2),choices[i]);
			if(i==chosen){
				attroff(A_STANDOUT);
			}
		}
		
		key = getch();
		if(key == 10 && chosen == 2){
			drawControls();
			key = 32;
		}
		clear();
	}
	
	return chosen;
}

void CGame::newGame(){
	// delete previous data
	if(c_map != NULL){
		delete c_map;
		c_map = NULL;
		c_player = NULL;
		c_creatures.clear();
	}
	
	mapSelection();
	roleEditor();
	prepareNewGame();
	enableContinue = true;
}

void CGame::roleEditor(){
	int cols, rows;
	getmaxyx(stdscr, rows, cols);
	char key=-1;
	int chosen=0;
	int firstline = (rows*0.1);
	// role selection (wizard, paladin, elf) cycle
	while(key != 10){ // 10 = enter
		clear();
		getmaxyx(stdscr,rows,cols);
		
		mvaddstr (firstline, (cols/2)-36,   "#####    ####   ##     ####      ####  ####   ##  ######  ####   #####  ");
		mvaddstr (firstline+1, (cols/2)-36, "##  ##  ##  ##  ##     ##        ##    ## ##  ##    ##   ##  ##  ##  ## ");
		mvaddstr (firstline+2, (cols/2)-36, "#####   ##  ##  ##     ####      ####  ## ##  ##    ##   ##  ##  #####  ");
		mvaddstr (firstline+3, (cols/2)-36, "##  ##  ##  ##  ##     ##        ##    ## ##  ##    ##   ##  ##  ##  ## ");
		mvaddstr (firstline+4, (cols/2)-36, "##   ##  ####   #####  ####      ####  ####   ##    ##    ####   ##   ##");


		//recognize arrow keys
		if(key == 4 || key == 3){ // LEFT or UP
			(chosen==0)?chosen=2:chosen--;
		}
		if(key == 5 || key == 2){ // RIGHT or DOWN
		(chosen==2)?chosen=0:chosen++;
		}
		



		// draw role logos
		if(chosen==0){
			attron(A_STANDOUT);
		}
		mvaddstr (firstline+8,  (cols/2)-29, "             ");
		mvaddstr (firstline+9,  (cols/2)-29, "   ^^        ");
		mvaddstr (firstline+10, (cols/2)-29, " < ** >      ");
		mvaddstr (firstline+11, (cols/2)-29, "   ||   '    ");
		mvaddstr (firstline+12, (cols/2)-29, "   || ' __ ' ");
		mvaddstr (firstline+13, (cols/2)-29, "   ||  /*.\\  ");
		mvaddstr (firstline+14, (cols/2)-29, "   ||  \\__/  ");
		mvaddstr (firstline+15, (cols/2)-29, "   || '      ");
		mvaddstr (firstline+16, (cols/2)-29, "   ||    '   ");
		mvaddstr (firstline+17, (cols/2)-29, "             ");
		if(chosen==0){
			attroff(A_STANDOUT);
			// draw description
			attron(A_BOLD);
			mvaddstr(firstline+20, (cols/2)-20, "Wizard");
			attroff(A_BOLD);
			mvaddstr(firstline+22, (cols/2)-20, "Very intelligent. Their learning speed is amazing.");
			mvaddstr(firstline+24, (cols/2)-20, "Leveling:      150%");
			mvaddstr(firstline+25, (cols/2)-20, "Skill points:  10");
		}
		if(chosen==1){
			attron(A_STANDOUT);
		}
		mvaddstr (firstline+8,  (cols/2)-5, "  __________  ");
		mvaddstr (firstline+9,  (cols/2)-5, " |    ||    | ");
		mvaddstr (firstline+10, (cols/2)-5, " |____||____| ");
		mvaddstr (firstline+11, (cols/2)-5, " |____  ____| ");
		mvaddstr (firstline+12, (cols/2)-5, " \\    ||    / ");
		mvaddstr (firstline+13, (cols/2)-5, "  \\   ||   /  ");
		mvaddstr (firstline+14, (cols/2)-5, "   \\  ||  /   ");
		mvaddstr (firstline+15, (cols/2)-5, "    \\ || /    ");
		mvaddstr (firstline+16, (cols/2)-5, "     \\||/     ");
		mvaddstr (firstline+17, (cols/2)-5, "      \\/      ");
		if(chosen==1){
			attroff(A_STANDOUT);
			// draw description
			attron(A_BOLD);
			mvaddstr(firstline+20, (cols/2)-20, "Palladin");
			attroff(A_BOLD);
			mvaddstr(firstline+22, (cols/2)-20, "Strong and brave. That's the palladin.");
			mvaddstr(firstline+24, (cols/2)-20, "Leveling:      100%");
			mvaddstr(firstline+25, (cols/2)-20, "Skill points:  30");
		}
		if(chosen==2){
			attron(A_STANDOUT);
		}
		mvaddstr (firstline+8,  (cols/2)+17, "     (.      ");
		mvaddstr (firstline+9,  (cols/2)+17, "     |\\      ");
		mvaddstr (firstline+10, (cols/2)+17, "     | \\     ");
		mvaddstr (firstline+11, (cols/2)+17, "     | .\\    ");
		mvaddstr (firstline+12, (cols/2)+17, " >---|--|--> ");
		mvaddstr (firstline+13, (cols/2)+17, "     | ./    ");
		mvaddstr (firstline+14, (cols/2)+17, "     | /     ");
		mvaddstr (firstline+15, (cols/2)+17, "     |/      ");
		mvaddstr (firstline+16, (cols/2)+17, "     (.      ");
		mvaddstr (firstline+17, (cols/2)+17, "             ");
		if(chosen==2){
			attroff(A_STANDOUT);
			// draw description
			attron(A_BOLD);
			mvaddstr(firstline+20, (cols/2)-20, "Elf");
			attroff(A_BOLD);
			mvaddstr(firstline+22, (cols/2)-20, "Universal and determined. Every enemy should run away.");
			mvaddstr(firstline+24, (cols/2)-20, "Leveling:      125%");
			mvaddstr(firstline+25, (cols/2)-20, "Skill points:  15");
		}
		key = getch();
	}
	// role selected, now select points
	key = -1;
	string name;
	int pointsLeft;
	int leveling;
	int pointsHealth=0;
	int pointsAttack=0;
	if(chosen==0){
		name = "Wizard";
		pointsLeft = 10;
		leveling = 150;
	}
	if(chosen==1){
		name = "Palladin";
		pointsLeft = 30;
		leveling = 100;
	}
	if(chosen==2){
		name = "Elf";
		pointsLeft = 15;
		leveling = 125;
	}
	chosen = 0;
	while( key != 10 ){
		// clean under logos
		for(int i=0; i<10; i++){
			mvaddstr(firstline+21+i, (cols/2)-36, "                                                                       ");
		}
		
		//recognize arrow keys
		if(key == 3){ // UP
			(chosen==0)?chosen=1:chosen--;
		}
		if(key == 2){ // DOWN
		(chosen==1)?chosen=0:chosen++;
		}
		if(key == 4){ // LEFT 
			if(chosen==0){
				if(pointsHealth > 0){
					pointsHealth--;
					pointsLeft++;
				}
			} else {
				if(pointsAttack > 0){
					pointsAttack--;
					pointsLeft++;
				}
			}
		}
		if(key == 5){ // RIGHT
			if(chosen==0){
				if(pointsLeft > 0){
					pointsHealth++;
					pointsLeft--;
				}
			} else {
				if(pointsLeft > 0){
					pointsAttack++;
					pointsLeft--;
				}
			}
		}
		
		
		if(chosen==0){
			attron(A_STANDOUT);
		}
		mvaddstr(firstline+22, (cols/2)-20, "Health");
		attroff(A_STANDOUT);
		for(int i=0; i<pointsHealth; i++){
			mvaddstr(firstline+22, (cols/2)-12+i, "#");
		}
		mvprintw(firstline+22, (cols/2)-11+pointsHealth, "%d", pointsHealth*10);
		if(chosen==1){
			attron(A_STANDOUT);
		}
		mvaddstr(firstline+24, (cols/2)-20, "Attack");
		attroff(A_STANDOUT);
		for(int i=0; i<pointsAttack; i++){
			mvaddstr(firstline+24, (cols/2)-12+i, "#");
		}
		mvprintw(firstline+24, (cols/2)-11+pointsAttack, "%d", pointsAttack);
		
		mvaddstr(firstline+26, (cols/2)-20, "Points left:");
		mvprintw(firstline+26, (cols/2)-20, "Points left:  %d", pointsLeft);
		key = getch();
	}
	// character selected
	c_player = new CPlayer(name,generatePlayerID(), pointsHealth*10, pointsAttack, leveling,'>', c_map);
}

void CGame::mapSelection(){ // loads c_map
	int cols, rows;
	getmaxyx(stdscr,rows,cols);
	char key=-1;
	int chosen=0;
	clear();
	
	// find .map files
	struct dirent *de=NULL;
	DIR *d=NULL;
	int i=0; // number of map files
	d=opendir(MAP_FOLDER.c_str());
	// Loop while not NULL
	vector<string> maps;
	while((de = readdir(d))){
		const char * one = ".";
		const char * two = "..";
		if( (strcmp(one,de->d_name)!=0) && (strcmp(two,de->d_name)!=0) ) {
			maps.push_back(de->d_name);
			maps[i] = maps[i].substr(0, maps[i].size()-4); // without ".map"
			i++;
		}
	}
	closedir(d);
	
	// map menu cycle
	while(key != 10){ // 10 = enter
		getmaxyx(stdscr,rows,cols);
		
		//recognize arrow keys
		if(key == 3){ // UP
			(chosen==0)?chosen=i-1:chosen--;
		}
		if(key == 2){ // DOWN
		(chosen==i-1)?chosen=0:chosen++;
		}
		
		mvaddstr ((rows*0.2), (cols/2)-31,   " ####   ####   ##     ####    ###  ######       ##   ##     ##     #### ");
		mvaddstr ((rows*0.2)+1, (cols/2)-31, "##      ##     ##     ##     ##      ##         ### ###   ##  ##   ## ##");
		mvaddstr ((rows*0.2)+2, (cols/2)-31, " ###    ####   ##     ####   ##      ##         ## # ##   ######   #### ");
		mvaddstr ((rows*0.2)+3, (cols/2)-31, "   ##   ##     ##     ##     ##      ##         ##   ##   ##  ##   ##   ");
		mvaddstr ((rows*0.2)+4, (cols/2)-31, "####    ####   ####   ####    ###    ##         ##   ##   ##  ##   ##   ");

		for(int j=0; j<i; j++){
			if(j==chosen){
				attron(A_STANDOUT);
			}
			const char * cstr = maps[j].c_str();
			mvaddstr((rows*0.2)+8+2*j, (cols/2)-(strlen(maps[j].c_str())/2),cstr);
			if(j==chosen){
				attroff(A_STANDOUT);
			}
		}
		key = getch();
		clear();
	}
	// map selected
	string selected = maps[chosen];
	selected += ".map";
	selected.insert(0,MAP_FOLDER);
	c_map = new CMap(selected);
}

void CGame::prepareNewGame(){
	// places the player
	int x,y;
	c_map->findFreePlace(x,y);
	c_player->setPosition(x,y);
	c_map->addCObj(c_player);
	
	// reset the stats
	for(int i=0; i<6; i++){
		c_events[i].clear();
	}
	c_creatures_killed = 0;
	
	// load all creatures 
	string line;
	ifstream fin(CREATURES_FILE.c_str());
	if( fin.fail() || fin.bad() ){
		endwin();
		cerr<<"List of creatures not opened."<<endl;
		exit(1);
	}
	while( getline(fin, line) ){
			if( line[0] == '#' || line.size() == 0){
				continue;
			}
			stringstream ss(line);
			// loaded, parse to prototype
			creature_prototype prt;
			ss >> prt.level_begin;
			ss >> prt.level_end;
			ss >> prt.health_max;
			ss >> prt.attack_max;
			ss >> skipws >> prt.design;
			getline(ss, prt.name);
			// put into prototype map
			for(int i=prt.level_begin; i<=prt.level_end; i++){
				c_creature_prototypes[i].push_back(prt);
			}
	}
	fin.close();
	// load items 
	line.clear();
	fin.open(ITEMS_FILE.c_str());
	if( fin.fail() || fin.bad() ){
		endwin();
		cerr<<"List of items not opened."<<endl;
		exit(1);
	}
	while( getline(fin, line) ){
			if( line[0] == '#' || line.size() == 0){
				continue;
			}
			stringstream ss(line);
			// loaded, parse to prototype
			item_prototype prt;
			ss >> prt.one_use;
			ss >> prt.level_begin;
			ss >> prt.level_end;
			ss >> prt.health;
			ss >> prt.attack;
			ss >> prt.experience;
			ss >> skipws >> prt.design;
			getline(ss, prt.name);
			// put into prototype map
			for(int i=prt.level_begin; i<=prt.level_end; i++){
				c_item_prototypes[i].push_back(prt);
			}
	}
	fin.close();
	
	generateItemsAndCreatures();
	
	// prepare for drawing
	d_activeItem = 0;
	
	addEvent(string("Try to survive. Good luck."));
}

int CGame::generateID(bool item){ // if false -> id for creatures > 10000
	static int last_item=2; // id must start from 2 (0 is empty space, 1 is wall)
	static int last_creature=10000; // id must start from 10000 - detecion, if it is creature or an item
	return (item)?++last_item:++last_creature;
}

int CGame::generatePlayerID(){
	static int last=1000000;
	return ++last;
}

void CGame::runCycle(){
		const int ESC_CODE = 27;
		const int P_CODE = 112;
		nodelay(stdscr, TRUE);
		int input=0;
		int ai_skip = 10;
		int ai_left = 10;
		int pl_health = 500;
		int pl_left = 500;
		
		// MAIN GAME CYCLE
		while( c_player->Health() > 0 && (input != ESC_CODE && input != P_CODE)){
				drawScreen();
				sleep(SLEEP_TIME);
				
				// update enemies
				if(ai_left == 0){
					updateAIStats();
					ai_left = ai_skip;
				} else {
					ai_left--;
				}
				
				// update player
				input = getch(); //get input
				if(input > 0){
					updatePlayerStats(input);
				}
				if(pl_left ==0){
					c_player->AddHealth(1);
					pl_left = pl_health;
				} else {
					pl_left--;
				}
				
				while( getch() > 0 );
		}
		if(c_player->Health() == 0){
			showGameOver();
		}
		nodelay(stdscr, FALSE);
}

void CGame::updatePlayerStats(int input){
	int level = c_player->Level();
	// move player
	int move=-1;
	switch(input){
		case 258: // down
			move = c_player->Move(c_player->DIRECTION_DOWN);
		break;
		case 259: // up 
			move = c_player->Move(c_player->DIRECTION_UP);
		break;
		case 260: // left
			move = c_player->Move(c_player->DIRECTION_LEFT);
		break;
		case 261: // right
			move = c_player->Move(c_player->DIRECTION_RIGHT);
		break;
	}
	// handle the collision
	if(move==1){ // wall
		addEvent(string("You hit a wall."));
	} else if(move>1) { // another object
		string ev(" found!");
		addEvent((*c_map).getObj(move)->Name().append(ev));
	}
	if(move!=-1) return;
	
	// items (take/drop)
	switch(input){
		case 97: // key "a" ... attack / take item
			{	// search near player if there is an item -> take it, if an enemy -> attack
				// first search in front of player, then around
				int x,y;
				int dir = c_player->Direction();
				int id_found=0;
				for(int i=0; i<4; i++){
					c_player->InFrontOf(x,y, dir);
					int id = (*c_map)[x][y];
					if( id > 1 ){
						id_found = id;
						break;
					}
					dir++;
					if(dir==4) dir=0;
				}
				if( id_found == 0){
					addEvent("Nothing to attack / take.");
					return;
				}
				// we found something -> item/enemy ?
				c_player->setDirection(dir);

				if(id_found > 1 && id_found < c_player->MAX_ID_ITEM){ // -> it is an item
					// find free slot
					int slot = c_player->FindFreeSlot(d_activeItem);
					if( slot == -1 ){
						addEvent("Your bag is full.");
					} else {
						// add item
						CItem * item = (CItem*)c_map->getObj(id_found);
						c_map->delCObj(item);
						c_player->AddItem(slot, item);
						d_activeItem = slot;
						
						// add an event
						string ev = item->Name();
						ev+=" taken.";
						addEvent(ev);
					}
				} else if( id_found > c_player->MAX_ID_ITEM ) { // -> it is an enemy
					// check attacking place
					CCreature * enemy = (CCreature*)c_map->getObj(id_found);
					int hit = enemy->Hit(c_player->Attack());
					c_player->AddExp(hit);
					if(enemy->Health() == 0){
						// enemy killed
						c_creatures_killed++;
						c_map->delCObj(enemy);
						stringstream ss;
						ss << enemy->Name() << " is no more.";
						addEvent(ss.str());
					} else {
						
						stringstream ss;
						ss << "You attacked " << enemy->Name() << " with damage " << hit;
						addEvent(ss.str());
					}
				} 
			}
		break;
		case 100: // key "d"
			{
				// drop selected item
				CItem * item = c_player->Item(d_activeItem);
				if(item == NULL){
					addEvent("No item to drop.");
				} else {
					int x,y;
					c_player->InFrontOf(x,y, c_player->Direction());
					if((*c_map)[x][y] != 0){
						addEvent("Not enough space for item.");
					} else {
						// possible to place
						item->setPosition(x,y);
						c_map->addCObj(item);
						c_player->DelItem(d_activeItem);
						int slot = c_player->FindFullSlot(d_activeItem);
						if(slot!=-1) d_activeItem = slot;
						
						string ev = item->Name();
						ev+=" was dropped.";
						addEvent(ev);
					}
				}
			}
		break;
		case 113: // key "q"
			// select previous item
			(d_activeItem==0)?d_activeItem=5:d_activeItem--;
		break;
		case 101: // key "e"
			// select next item
			(d_activeItem==5)?d_activeItem=0:d_activeItem++;
		break;
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
			// select the item
			d_activeItem = input-49;
		break;
		case 32: // 'spacebar'
			// use item
			CItem * item = c_player->Item(d_activeItem);
			if( item == NULL){
				addEvent("No item to use.");
			} else {
				if( !item->Usable() ){
					string ev=item->Name();
					ev+=" has permanent effect.";
					addEvent(ev);
				} else {
					string ev=item->Name();
					ev+=" was used.";
					c_player->UseItem(d_activeItem);
					addEvent(ev);
					int slot = c_player->FindFullSlot(d_activeItem);
					if(slot!=-1) d_activeItem = slot;
				}
			}
		break;
	}
	
	// check level change
	if( level < c_player->Level() ){
		stringstream ss;
		ss << c_player->Name() << " level " << c_player->Level() << "!";
		addEvent(ss.str());
	}
} 

void CGame::updateAIStats(){
	// let the creatures know, where is the player
	int x,y;
	c_player->Position(x,y);
	c_map->setPlayerXY(x,y);
	
	if(c_creatures.size() == 0){
		generateItemsAndCreatures();
		addEvent("New round is coming!");
	}
	
	for(int i=0; i<(int)c_creatures.size(); i++){
		CCreature * creature = c_creatures[i];
		// check if it is not dead
		if( creature->Health() == 0 ){
			// delete creature
			c_map->delCObj(creature);
			delete creature;
			c_creatures.erase(c_creatures.begin()+i);
			continue;
		}
		
		
		
		// Hey creature, try to think!
		int result = creature->AI();
		switch(result){
			case 0: // move
			case 1:
			case 2:
			case 3:
				creature->Move(result);
			break;
			case 4: // attack
			case 5:
			case 6:
			case 7:
				int hit = c_player->Hit(creature->Attack());
				
				stringstream ss;
				ss <<creature->Name() << " attacked you with damage " << hit;
				addEvent(ss.str());
			break;
		}
	}
}

void CGame::generateItemsAndCreatures(){
	static int count=1;
	// GENERATE NEW CREATURE(S) and ITEMS
	// generate items 
	int x,y;
	int i = (rand()%3)+3;
	for(int j=0;j<i; j++){
		CObj * item = generateItem();
		c_map->findFreePlace(x,y);
		item->setPosition(x,y);
		c_map->addCObj(item);
	}
	// generate enemies 
	i = (rand()%count)+3;
	for(int j=0; j<i; j++){
		CObj * enemy = generateCreature();
		c_map->findFreePlace(x,y);
		enemy->setPosition(x,y);
		c_map->addCObj(enemy);
		c_creatures.push_back((CCreature*)enemy);
	}
	count++;
}

CCreature * CGame::generateCreature(){
	int selection = c_creature_prototypes[c_player->Level()].size();
	creature_prototype prt = c_creature_prototypes[c_player->Level()][rand()%selection];
	return new CCreature(prt.name, generateID(), prt.health_max, prt.attack_max, prt.design, c_map);
}

CItem * CGame::generateItem(){
	int selection = c_item_prototypes[c_player->Level()].size();
	item_prototype prt = c_item_prototypes[c_player->Level()][rand()%selection];
	return new CItem(prt.name,generateID(true), prt.design,prt.health, prt.attack, prt.experience, prt.one_use); 
}

void CGame::addEvent(std::string event){
	c_events[5] = c_events[4];
	c_events[4] = c_events[3];
	c_events[3] = c_events[2];
	c_events[2] = c_events[1];
	c_events[1] = c_events[0];
	c_events[0] = event;
}

void CGame::drawControls() const{
	clear();
	int cols, rows;
	getmaxyx(stdscr,rows,cols);
	
	mvaddstr ((rows*0.2),   (cols/2)-30, " ####   ####   ##   ##  ######  #####     ####   ##      ####");
	mvaddstr ((rows*0.2)+1, (cols/2)-30, "##     ##  ##  ###  ##    ##    ##  ##   ##  ##  ##     ##   ");
	mvaddstr ((rows*0.2)+2, (cols/2)-30, "##     ##  ##  #### ##    ##    #####    ##  ##  ##      ### ");
	mvaddstr ((rows*0.2)+3, (cols/2)-30, "##     ##  ##  ## ####    ##    ##  ##   ##  ##  ##        ##");
	mvaddstr ((rows*0.2)+4, (cols/2)-30, " ####   ####   ##  ###    ##    ##   ##   ####   #####  #### ");
	
	
	mvaddstr ((rows*0.2)+7,  (cols/2)-18,              "  ARROWS   Move.");
	mvaddstr ((rows*0.2)+8,  (cols/2)-18,              "   SPACE   Use selected item.");
	mvaddstr ((rows*0.2)+9,  (cols/2)-18,              " NUM 1-6   Select item.");
	mvaddstr ((rows*0.2)+10, (cols/2)-18,              "       A   Attack an enemy / Take an item.");
	mvaddstr ((rows*0.2)+11, (cols/2)-18,              "       D   Drop selected item .");
	mvaddstr ((rows*0.2)+12, (cols/2)-18,              "       Q   Select previous item.");
	mvaddstr ((rows*0.2)+13, (cols/2)-18,              "       E   Select next item.");
	mvaddstr ((rows*0.2)+14, (cols/2)-18,              "ESC or P   Pause / Go to menu.");
	
	mvaddstr((rows*0.2)+17, (cols/2)-11 ,"Press any key to return.");
	getch();
}

void CGame::drawScreen(){
	int rows, cols, halfcols, halfrows;
	getmaxyx(stdscr,rows,cols);
	halfrows = rows/2;
	halfcols = cols/2;
	int offset_x, offset_y;

	// draw all points
	string points;
	c_player->Position(offset_x, offset_y);
	points.resize(cols,'.');
	for(int y=0; y<rows; y++){
		mvaddstr(y,0,points.c_str());
	}
	// draw map
	for(unsigned i=0; i<c_map->getHeight(); i++){
		for(unsigned j=0; j<c_map->getWidth(); j++){
			if((*c_map)[j][i]==1){
				mvaddch( (halfrows)+i-offset_y,(halfcols)+j-offset_x,'#'); // vykresleni zdi
			} else if ((*c_map)[j][i]==0){
				mvaddch( (halfrows)+i-offset_y,(halfcols)+j-offset_x,' '); // volno
			} else if ((*c_map)[j][i]<0){
				mvaddch( (halfrows)+i-offset_y,(halfcols)+j-offset_x,'.'); // nedostupne volno
			} else {
				// objekt -> draw Sprite
				int id = (*c_map)[j][i];
				CObj * obj = c_map->getObj(id);
				if( id < obj->MAX_ID_ITEM ){
					// item
					attron(A_DIM);
					mvaddch((halfrows)+i-offset_y,(halfcols)+j-offset_x,obj->Design());
					attroff(A_DIM);
				} else if ( id < obj->MAX_ID_CREATURE ){
					// enemy
					attron(A_BOLD);
					mvaddch((halfrows)+i-offset_y,(halfcols)+j-offset_x,obj->Design());
					attroff(A_BOLD);
				} else {
					// player
					attron(A_BOLD);
					mvaddch((halfrows)+i-offset_y,(halfcols)+j-offset_x,obj->Design());
					attroff(A_BOLD);
				}
			}
		}
	}
	// draw STATUS FRAME
	mvaddstr(0, 0, "  ________________  ");
	mvaddstr(1, 0, " |              % | ");
	mvaddstr(2, 0, " | -------------- | ");
	mvaddstr(3, 0, " | Level:         | ");
	mvaddstr(4, 0, " | Health:        | ");
	mvaddstr(5, 0, " | Attack:        | ");
	mvaddstr(6, 0, " | Items:         | ");
	mvaddstr(7, 0, " |                | ");
	mvaddstr(8, 0, " |                | ");
	mvaddstr(9, 0, " |                | ");
	mvaddstr(10,0, " |                | ");
	mvaddstr(11,0, " |                | ");
	mvaddstr(12,0, " |                | ");
	mvaddstr(13,0, " |                | ");
	mvaddstr(14,0, " |________________| ");
	mvaddstr(15,0, "                    ");
	// draw stats in it
	attron(A_BOLD);
	mvaddstr(1, 3, c_player->Name().c_str()); 
	mvprintw(1, 14,"%2d",c_player->Percentage());
	mvprintw(3, 14,"%3d",c_player->Level());
	mvprintw(4, 10,"%3d/%3d",c_player->Health(),c_player->MaxHealth());
	mvprintw(5, 14,"%3d",c_player->Attack());
	attroff(A_BOLD);
	for(int i=0; i<6; i++){
		CItem * item = c_player->Item(i);
		if(i==d_activeItem){
			attron(A_STANDOUT);
		}
		mvprintw(8+i, 4, "%d:",i+1);
		if(item != NULL){
			mvprintw(8+i, 6, "%11s",c_player->Item(i)->Name().c_str());
		}
		if(i==d_activeItem){
			attroff(A_STANDOUT);
		}
	}
	
	// draw ENEMY FRAMES
	int x,y, dr, enemies; // dr...direction
	enemies=0;
	int xmv[] = {0,1,0,-1};
	int ymv[] = {-1,0,1,0};
	c_player->Position(x,y);
	dr = c_player->Direction();

	for(int i=0; i<4; i++){
		int id = (*c_map)[ x+xmv[dr%4] ][ y+ymv[dr%4] ];
		if( id > 10000 ){ // -> enemy
			CCreature * obj = (CCreature*)c_map->getObj(id);
			mvaddstr(0+(enemies*6), cols-20, "  ________________  ");
			mvaddstr(1+(enemies*6), cols-20, " |                | ");
			mvaddstr(2+(enemies*6), cols-20, " | -------------- | ");
			mvaddstr(3+(enemies*6), cols-20, " | Health:        | ");
			mvaddstr(4+(enemies*6), cols-20, " | Attack:        | ");
			mvaddstr(5+(enemies*6), cols-20, " |________________| ");
			mvaddstr(6+(enemies*6), cols-20, "                    ");
			attron(A_BOLD);
				mvaddstr(1+(enemies*6),cols-17, obj->Name().c_str());
				mvprintw(3+(enemies*6),cols-6, "%3d",obj->Health());
				mvprintw(4+(enemies*6),cols-6, "%3d",obj->Attack());
			attroff(A_BOLD);
			enemies++;
		}
		dr++;
	}
	
	
	// draw ITEM INFO
	CItem * item = c_player->Item(d_activeItem);
	if(item != NULL){
		mvaddstr(rows-14,0, "  ________________  ");
		mvaddstr(rows-13,0, " |  Item detail   | ");
		mvaddstr(rows-12,0, " | -------------- | ");
		mvaddstr(rows-11,0, " | Name:          | ");
		mvaddstr(rows-10, 0," |                | ");
		mvaddstr(rows-9, 0, " |                | ");
		mvaddstr(rows-8, 0, " |                | ");
		mvaddstr(rows-7, 0, " | Effect:        | ");
		mvaddstr(rows-6, 0, " |                | ");
		mvaddstr(rows-5, 0, " |                | ");
		mvaddstr(rows-4, 0, " |                | ");
		mvaddstr(rows-3, 0, " |                | ");
		mvaddstr(rows-2, 0, " |________________| ");
		mvaddstr(rows-1, 0, "                    ");
		// draw info in it
		attron(A_BOLD);
		mvaddstr(rows-9,3, item->Name().c_str());
		int j=0;
		if(item->Attack() != 0){
			mvprintw(rows-5+j,3, "+%d attack", item->Attack());
			j++;
		}
		if(item->Health() != 0){
			mvprintw(rows-5+j,3, "+%d health", item->Health());
			j++;
		}
		if(item->Exp() != 0){
			mvprintw(rows-5+j,3, "+%d experience", item->Exp());
			j++;
		}
		attroff(A_BOLD);
		mvaddstr(rows-5+j,3, (item->Usable())?"For one use.":"");
	}
	
	// draw EVENT FRAME
	mvaddstr(rows-9, (cols)-41, "  _____________________________________  ");
	mvaddstr(rows-8, (cols)-41, " |                                     | ");
	mvaddstr(rows-7, (cols)-41, " |                                     | ");
	mvaddstr(rows-6, (cols)-41, " |                                     | ");
	mvaddstr(rows-5, (cols)-41, " |                                     | ");
	mvaddstr(rows-4, (cols)-41, " |                                     | ");
	mvaddstr(rows-3, (cols)-41, " |                                     | ");
	mvaddstr(rows-2, (cols)-41, " |_____________________________________| ");
	mvaddstr(rows-1, (cols)-41, "           Press \"P\" to menu.          ");
	// draw events in it
	mvaddstr(rows-8, (cols)-20-(c_events[0].size()/2), c_events[0].c_str());
	mvaddstr(rows-7, (cols)-20-(c_events[1].size()/2), c_events[1].c_str());
	mvaddstr(rows-6, (cols)-20-(c_events[2].size()/2), c_events[2].c_str());
	mvaddstr(rows-5, (cols)-20-(c_events[3].size()/2), c_events[3].c_str());
	mvaddstr(rows-4, (cols)-20-(c_events[4].size()/2), c_events[4].c_str());
	mvaddstr(rows-3, (cols)-20-(c_events[5].size()/2), c_events[5].c_str());
}

void CGame::showGameOver(){
	clear();
	int rows, cols;
	getmaxyx(stdscr,rows,cols);
	
	mvaddstr ((rows*0.2),   (cols/2)-33, " #####     ##    ##   ##  ####        ####   ##  ##  ####  #####  ");
	mvaddstr ((rows*0.2)+1, (cols/2)-33, "##       ##  ##  ### ###  ##         ##  ##  ##  ##  ##    ##  ## ");
	mvaddstr ((rows*0.2)+2, (cols/2)-33, "## ###   ######  ## # ##  ####       ##  ##  ##  ##  ####  #####  ");
	mvaddstr ((rows*0.2)+3, (cols/2)-33, "##   ##  ##  ##  ##   ##  ##         ##  ##  ######  ##    ##  ## ");
	mvaddstr ((rows*0.2)+4, (cols/2)-33, " #####   ##  ##  ##   ##  ####        ####     ##    ####  ##   ##");
	attron(A_BOLD);
	mvprintw((rows*0.2)+10, (cols/2)-18,"%s (level %d) died.", c_player->Name().c_str(), c_player->Level());
	attroff(A_BOLD);
	mvprintw((rows*0.2)+12, (cols/2)-18,"You killed %d creatures",c_creatures_killed);
	
	mvaddstr ((rows*0.2)+17, (cols/2)-33, "               Press 'enter' to heaven.");
	enableContinue = false;
	while( getch() != 10){};

}

void CGame::sleep(long us){
	struct timespec wait;
	wait.tv_sec = us / (1000 * 1000);
	wait.tv_nsec = (us % (1000 * 1000)) * 1000;
	nanosleep(&wait, NULL);
}
