# Makefile meant to be used with MinGW-w64 or on Linux

BIN_NAME=triangle
INCLUDE=-Igllibs/include

LINUX_CC=cc
LINUX_LINK_DIR=-Llib/linux
MINGW_LINK_DIR=-Llib/mingw
LINUX_LD_FLAGS=-lglfw3 -lSOIL2 -lm -lGL
MINGW_LD_FLAGS=-lglfw -lsoil2 -lm

GLAD_SRC=gllibs/lib/glad.c

# Linux 
output:
	${LINUX_CC} triangle.c ${GLAD_SRC} -o ${BIN_NAME} ${LINUX_LINK_DIR} ${LINUX_LD_FLAGS}

# MinGW
mingw-output:
	gcc triangle.c ${GLAD_SRC} -o ${BIN_NAME} ${MINGW_LINK_DIR} ${MINGW_LD_FLAGS}

run:
	./${BIN_NAME}

clean:
	rm -f ${BIN_NAME}

