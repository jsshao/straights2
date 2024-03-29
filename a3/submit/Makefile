TYPE:=int
BTYPE:=int
SENTINEL:=-1
KIND:=NOBUSY
OPT:=-O2

CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD ${OPT} \
	 -DTYPE="${TYPE}" -DBTYPE="${BTYPE}" -DSENTINEL="${SENTINEL}" -D"${KIND}" # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = q1mergesort.o
EXEC1 = mergesort

OBJECTS2 = q2buffer.o q2consumer.o q2producer.o q2.o
EXEC2 = buffer

OBJECTS = ${OBJECTS1} ${OBJECTS2}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1} ${EXEC2} 			# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

-include ImplType

ifeq (${IMPLTYPE},${TYPE})			# same implementation type as last time ?
${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${TYPE},)					# no implementation type specified ?
# set type to previous type
TYPE=${IMPLTYPE}
${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC1}
${EXEC1} :
	rm -f ImplType
	touch q1${EXEC1}.h
	sleep 1
	${MAKE} ${EXEC1} TYPE="${TYPE}"
endif
endif

ImplType :
	echo "IMPLTYPE=${TYPE}" > ImplType

#############################################################

-include ImplKind

ifeq (${IMPLKIND},${KIND})			# same implementation type as last time ?
${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@
else
ifeq (${KIND},)					# no implementation type specified ?
# set type to previous type
KIND=${IMPLKIND}
${EXEC2} : ${OBJECTS2}
	${CXX} ${CXXFLAGS} $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC2}
${EXEC2} :
	rm -f ImplKind
	touch q2${EXEC2}.h
	sleep 1
	${MAKE} ${EXEC2} KIND=${KIND}
endif
endif

ImplKind :
	echo "IMPLKIND=${KIND}" > ImplKind

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplType ImplKind
