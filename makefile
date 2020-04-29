DIR_INC = ./inc
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_LIB = ./lib
CSRC = $(wildcard ${DIR_SRC}/*.c)
COBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${CSRC}))
CFLAGS =-I${DIR_INC} -I/opt/app/infrared/curl-lib/include
CLDFLAGS =-L/opt/app/infrared/curl-lib/lib -lcurl -lpthread
CROSS_COMPILE = /opt/gcc-linaro-4.9-2014.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
TARGET = libdeviceagent.so
BIN_TARGET = ${DIR_LIB}/${TARGET}


CXX = $(CROSS_COMPILE)
${BIN_TARGET}:${COBJ}
	$(CXX) ${COBJ} $(CLDFLAGS) -shared -o $@ -lm

${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CXX) $(CFLAGS) -c -fPIC $^ -o $@

.PHONY:clean
clean:
	rm -rf  ${DIR_OBJ}/*
	rm -rf  ${DIR_LIB}/*

