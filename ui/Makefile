CXX = g++ 
CXXFLAGS = -g -O0 `pkg-config --cflags gtkmm-2.4`  -Wall -MMD 
OBJECTS = main.o GUIWindow.o DeckGUI.o 
DEPENDS = ${OBJECTS:.o=.d} 
EXEC = ui
LIBS = `pkg-config --libs gtkmm-2.4` 
${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBS}
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
-include ${DEPENDS}
