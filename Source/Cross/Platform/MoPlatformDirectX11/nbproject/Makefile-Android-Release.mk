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
CND_PLATFORM=Android-Windows
CND_DLIB_EXT=dll
CND_CONF=Android-Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/FEoDeviceConsole.o \
	${OBJECTDIR}/FEoDisplayColorEffect.o \
	${OBJECTDIR}/FEoDisplayColorTechnique.o \
	${OBJECTDIR}/FEoDisplayTextureEffect.o \
	${OBJECTDIR}/FEoDisplayTextureTechnique.o \
	${OBJECTDIR}/FEoFont.o \
	${OBJECTDIR}/FEoFontConsole.o \
	${OBJECTDIR}/FEoRenderCubeTexture.o \
	${OBJECTDIR}/FEoRenderDevice.o \
	${OBJECTDIR}/FEoRenderFlatTexture.o \
	${OBJECTDIR}/FEoRenderFragmentShader.o \
	${OBJECTDIR}/FEoRenderIndexBuffer.o \
	${OBJECTDIR}/FEoRenderProgram.o \
	${OBJECTDIR}/FEoRenderVertexBuffer.o \
	${OBJECTDIR}/FEoRenderVertexShader.o \
	${OBJECTDIR}/FEoTechniqueConsole.o \
	${OBJECTDIR}/MoEngineOpenGL.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-jvmopt=-Xmx2G -emit-llvm -O4
CXXFLAGS=-jvmopt=-Xmx2G -emit-llvm -O4

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmoengineopengl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmoengineopengl.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmoengineopengl.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmoengineopengl.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmoengineopengl.a

${OBJECTDIR}/FEoDeviceConsole.o: FEoDeviceConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoDeviceConsole.o FEoDeviceConsole.cpp

${OBJECTDIR}/FEoDisplayColorEffect.o: FEoDisplayColorEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoDisplayColorEffect.o FEoDisplayColorEffect.cpp

${OBJECTDIR}/FEoDisplayColorTechnique.o: FEoDisplayColorTechnique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoDisplayColorTechnique.o FEoDisplayColorTechnique.cpp

${OBJECTDIR}/FEoDisplayTextureEffect.o: FEoDisplayTextureEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoDisplayTextureEffect.o FEoDisplayTextureEffect.cpp

${OBJECTDIR}/FEoDisplayTextureTechnique.o: FEoDisplayTextureTechnique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoDisplayTextureTechnique.o FEoDisplayTextureTechnique.cpp

${OBJECTDIR}/FEoFont.o: FEoFont.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoFont.o FEoFont.cpp

${OBJECTDIR}/FEoFontConsole.o: FEoFontConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoFontConsole.o FEoFontConsole.cpp

${OBJECTDIR}/FEoRenderCubeTexture.o: FEoRenderCubeTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderCubeTexture.o FEoRenderCubeTexture.cpp

${OBJECTDIR}/FEoRenderDevice.o: FEoRenderDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderDevice.o FEoRenderDevice.cpp

${OBJECTDIR}/FEoRenderFlatTexture.o: FEoRenderFlatTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderFlatTexture.o FEoRenderFlatTexture.cpp

${OBJECTDIR}/FEoRenderFragmentShader.o: FEoRenderFragmentShader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderFragmentShader.o FEoRenderFragmentShader.cpp

${OBJECTDIR}/FEoRenderIndexBuffer.o: FEoRenderIndexBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderIndexBuffer.o FEoRenderIndexBuffer.cpp

${OBJECTDIR}/FEoRenderProgram.o: FEoRenderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderProgram.o FEoRenderProgram.cpp

${OBJECTDIR}/FEoRenderVertexBuffer.o: FEoRenderVertexBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderVertexBuffer.o FEoRenderVertexBuffer.cpp

${OBJECTDIR}/FEoRenderVertexShader.o: FEoRenderVertexShader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoRenderVertexShader.o FEoRenderVertexShader.cpp

${OBJECTDIR}/FEoTechniqueConsole.o: FEoTechniqueConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/FEoTechniqueConsole.o FEoTechniqueConsole.cpp

${OBJECTDIR}/MoEngineOpenGL.o: MoEngineOpenGL.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -w -s -D_MO_EF_EXPORTS -D_MO_FLASCC -D_MO_FLASH -D_MO_X86 -I../../../Studio/SDK/flascc_1.0.0/sdk/usr/include -I../../Library/MoLzma -I../../Library/MoJpeg -I../../Common/MoCommon -I../MoEngine -o ${OBJECTDIR}/MoEngineOpenGL.o MoEngineOpenGL.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmoengineopengl.a

# Subprojects
.clean-subprojects:
