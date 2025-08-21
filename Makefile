CC = gcc
#CFLAGS = -Wall -Wextra -std=c11 -O2 -g -mavx2
CFLAGS = -O2 -mavx2
INCLUDES = -Isrc
LDFLAGS = -lm

SRC_DIR = src
BUILD_DIR = build
CODE_DIR = code

LIB_DIR = libs
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

LIB_FILES = $(wildcard $(LIB_DIR)/*.c)
SO_FILES = $(patsubst $(LIB_DIR)/%.c,$(BIN_DIR)/%.so,$(LIB_FILES))

TARGET = $(BUILD_DIR)/Main

all:
	$(CC) $(CFLAGS) $(INCLUDES) ./$(SRC_DIR)/Main.c -o ./$(TARGET) $(LDFLAGS) 

clean:
	rm -rf $(BUILD_DIR)/*

lib: $(SO_FILES)

$(BIN_DIR)/%.so: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -o $@ $< -shared $(LDFLAGS)

win:
	$(CC) $(CFLAGS) -fPIC -o ./$(BIN_DIR)/window.so ./$(LIB_DIR)/window.c -shared $(LDFLAGS) -lX11 -lpng

cleanlib:
	rm -rf $(BIN_DIR)/*

exe:
	./$(TARGET) ./code/Function.ll

do: clean all exe