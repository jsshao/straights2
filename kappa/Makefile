TYPE:=int
SENTINEL:=-1

CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -DTYPE="${TYPE}" -DSENTINEL="${SENTINEL}" # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = # object files forming 1st executable with prefix "q1"
EXEC1 = binsertsort

OBJECTS2 = # object files forming 2st executable with prefix "q2"
EXEC2 = cardgame

OBJECTS = ${OBJECTS1} ${OBJECTS2}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC2}			# all executables

.PHONY : all clean

all : ${EXECS}					# build all executables

#############################################################

-include ImplType

ifeq (${IMPLTYPE},${TYPE})			# same implementation type as last time ?
${EXEC1} : ${OBJECTS1}
	${CXX} q1.cc ${CXXFLAGS} $^ -o $@
else
ifeq (${TYPE},)					# no implementation type specified ?
# set type to previous type
TYPE=${IMPLTYPE}
${EXEC1} : ${OBJECTS1}
	${CXX} q1.cc ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC1}
${EXEC1} :
	rm -f ImplType
	touch q1${EXEC1}.h
	sleep 1
	${MAKE} TYPE="${TYPE}" SENTINEL="${SENTINEL}"
endif
endif

ImplType :
	echo "IMPLTYPE=${TYPE}" > ImplType

${EXEC2} : ${OBJECTS2}				# link step 2nd executable
	${CXX} q2.cc ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplType
