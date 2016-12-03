CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
OBJECTS = boardobject.o chamber.o character.o dragon.o dwarf.o elf.o enemy.o floor.o goblin.o gold.o human.o main.o merchant.o orc.o phoenix.o player.o potion.o stairs.o textdisplay.o tile.o troll.o vampire.o werewolf.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
