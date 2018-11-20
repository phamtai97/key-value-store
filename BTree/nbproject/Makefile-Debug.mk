#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BytesDataInputStore.o \
	${OBJECTDIR}/BytesDataOutputStore.o \
	${OBJECTDIR}/DataInput.o \
	${OBJECTDIR}/DataOutput.o \
	${OBJECTDIR}/ManageFileRead.o \
	${OBJECTDIR}/ManageFileWrite.o \
	${OBJECTDIR}/Printer.o \
	${OBJECTDIR}/Server.o \
	${OBJECTDIR}/SocketClient.o \
	${OBJECTDIR}/StringStringComparator.o \
	${OBJECTDIR}/ThreadPool.o \
	${OBJECTDIR}/Worker.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pthread -lboost_system -lboost_thread
CXXFLAGS=-pthread -lboost_system -lboost_thread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/include/boost

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/btree

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/btree: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/btree ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/BytesDataInputStore.o: BytesDataInputStore.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BytesDataInputStore.o BytesDataInputStore.cpp

${OBJECTDIR}/BytesDataOutputStore.o: BytesDataOutputStore.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BytesDataOutputStore.o BytesDataOutputStore.cpp

${OBJECTDIR}/DataInput.o: DataInput.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataInput.o DataInput.cpp

${OBJECTDIR}/DataOutput.o: DataOutput.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataOutput.o DataOutput.cpp

${OBJECTDIR}/ManageFileRead.o: ManageFileRead.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ManageFileRead.o ManageFileRead.cpp

${OBJECTDIR}/ManageFileWrite.o: ManageFileWrite.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ManageFileWrite.o ManageFileWrite.cpp

${OBJECTDIR}/Printer.o: Printer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Printer.o Printer.cpp

${OBJECTDIR}/Server.o: Server.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server.o Server.cpp

${OBJECTDIR}/SocketClient.o: SocketClient.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SocketClient.o SocketClient.cpp

${OBJECTDIR}/StringStringComparator.o: StringStringComparator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StringStringComparator.o StringStringComparator.cpp

${OBJECTDIR}/ThreadPool.o: ThreadPool.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ThreadPool.o ThreadPool.cpp

${OBJECTDIR}/Worker.o: Worker.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Worker.o Worker.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
