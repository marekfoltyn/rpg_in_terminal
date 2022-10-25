#Author: Marek Foltýn
#foltyma1@fit.cvut.cz

OBJ=src/bin/main.o src/bin/CGame.o src/bin/CPlayer.o src/bin/CCreature.o src/bin/CItem.o src/bin/CLiveObj.o src/bin/CMap.o src/bin/CObj.o
DOX=Doxyfile
OUT=./foltyma1
MKD=mkdir -p src/bin

all: $(OBJ) $(DOX)
	make compile
	make doc

compile: $(OUT)

$(OUT): $(OBJ)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb $(OBJ) -o $(OUT) -lncurses

run: $(OUT)
	$(OUT)

clean:
	rm -rf src/bin doc $(OUT)
	
doc: src/$(DOX) src/*
	(rm -rf doc; cd src ; doxygen $(DOX) 2> /dev/null > /dev/null )

$(DOX): src/$(DOX)

src/bin/CObj.o: src/CObj.cpp src/CObj.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@

src/bin/CCreature.o: src/CCreature.cpp src/CCreature.hpp src/CLiveObj.hpp src/CMap.hpp src/CObj.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@

src/bin/CGame.o: src/CGame.cpp src/CGame.hpp src/CPlayer.hpp src/CLiveObj.hpp src/CMap.hpp src/CObj.hpp src/CItem.hpp src/CCreature.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@

src/bin/CItem.o: src/CItem.cpp src/CItem.hpp src/CObj.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@

src/bin/CLiveObj.o: src/CLiveObj.cpp src/CLiveObj.hpp src/CMap.hpp src/CObj.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@

src/bin/CMap.o: src/CMap.cpp src/CMap.hpp src/CObj.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@

src/bin/CPlayer.o: src/CPlayer.cpp src/CPlayer.hpp src/CLiveObj.hpp src/CMap.hpp src/CObj.hpp src/CItem.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@ 

src/bin/main.o: src/main.cpp src/CGame.hpp src/CPlayer.hpp src/CLiveObj.hpp src/CMap.hpp src/CObj.hpp src/CItem.hpp src/CCreature.hpp
	$(MKD)
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -c $< -o $@
