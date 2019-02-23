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
	${OBJECTDIR}/_ext/e1dda48/camera_base.o \
	${OBJECTDIR}/_ext/e1dda48/camera_lucid_triton.o \
	${OBJECTDIR}/_ext/e1dda48/error_base.o \
	${OBJECTDIR}/_ext/e1dda48/stopwatch.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-DTC_USE_TRITON
CXXFLAGS=-DTC_USE_TRITON

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/data/software/ArenaSDK_Linux_x64/lib64 -L/data/software/ArenaSDK_Linux_x64/ffmpeg -L/data/software/ArenaSDK_Linux_x64/GenICam/library/lib/Linux64_x64 `pkg-config --libs opencv` -larena -lgentl -lGCBase_gcc421_v3_0 -lGenApi_gcc421_v3_0  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucid-test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucid-test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucid-test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/e1dda48/camera_base.o: ../libterraclear/src/camera_base.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e1dda48
	${RM} "$@.d"
	$(COMPILE.cc) -g -I.. -I/data/software/ArenaSDK_Linux_x64/include/Arena -I/data/software/ArenaSDK_Linux_x64/GenICam/library/CPP/include `pkg-config --cflags opencv`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e1dda48/camera_base.o ../libterraclear/src/camera_base.cpp

${OBJECTDIR}/_ext/e1dda48/camera_lucid_triton.o: ../libterraclear/src/camera_lucid_triton.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e1dda48
	${RM} "$@.d"
	$(COMPILE.cc) -g -I.. -I/data/software/ArenaSDK_Linux_x64/include/Arena -I/data/software/ArenaSDK_Linux_x64/GenICam/library/CPP/include `pkg-config --cflags opencv`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e1dda48/camera_lucid_triton.o ../libterraclear/src/camera_lucid_triton.cpp

${OBJECTDIR}/_ext/e1dda48/error_base.o: ../libterraclear/src/error_base.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e1dda48
	${RM} "$@.d"
	$(COMPILE.cc) -g -I.. -I/data/software/ArenaSDK_Linux_x64/include/Arena -I/data/software/ArenaSDK_Linux_x64/GenICam/library/CPP/include `pkg-config --cflags opencv`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e1dda48/error_base.o ../libterraclear/src/error_base.cpp

${OBJECTDIR}/_ext/e1dda48/stopwatch.o: ../libterraclear/src/stopwatch.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e1dda48
	${RM} "$@.d"
	$(COMPILE.cc) -g -I.. -I/data/software/ArenaSDK_Linux_x64/include/Arena -I/data/software/ArenaSDK_Linux_x64/GenICam/library/CPP/include `pkg-config --cflags opencv`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e1dda48/stopwatch.o ../libterraclear/src/stopwatch.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I.. -I/data/software/ArenaSDK_Linux_x64/include/Arena -I/data/software/ArenaSDK_Linux_x64/GenICam/library/CPP/include `pkg-config --cflags opencv`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
