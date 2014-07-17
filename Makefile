CXX = g++ 
CXXFLAGS = -g -Wall -MMD 
OBJECTS = Card.o Command.o Deck.o Strategy.o HumanStrategy.o ComputerStrategy.o RageQuit.o Player.o Game.o Main.o 
DEPENDS = ${OBJECTS:.o=.d} 
EXEC = straights
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
-include ${DEPENDS}
