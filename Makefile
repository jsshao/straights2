CXX = g++ 
CXXFLAGS = -g -O0 `pkg-config --cflags gtkmm-2.4`  -Wall -MMD 
OBJECTS = Card.o Deck.o Player.o Game.o Main.o DeckGUI.o View.o Controller.o Model.o Subject.o
DEPENDS = ${OBJECTS:.o=.d} 
EXEC = straights
LIBS = `pkg-config --libs gtkmm-2.4` 
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBS}
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
-include ${DEPENDS}
