
BIN ?= xrr_map
PREFIX ?= /usr/local

SRC_DIR = ./src
BIN_DIR = ./bin
OBJ_DIR = $(SRC_DIR)/obj

CC := gcc
CFLAGS := -Wall -O2
LFLAGS := -lX11 -lXrandr -lXi

SOURCE := xrr_mapMonitor.c xrr_routines.c xrr_util.c
OBJS   := $(SOURCE:%.c=$(OBJ_DIR)/%.o)

$(BIN_DIR)/$(BIN): $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@ 

#xrr_mapMonitor.o: xrr.h  xrr_mapMonitor.cpp
#	(CC) (CFLAGS) -c xrr_mapMonitor.cpp 

#xrr_util.o: xrr.h xrr_util.cpp
#	(CC) (CFLAGS) -c xrr_util.cpp 

$(OBJ_DIR)/%.o:  $(SRC_DIR)/%.c $(SRC_DIR)/xrr.h | $(BIN_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

install:
	install ./$(BIN_DIR)/$(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm $(PREFIX)/bin/$(BIN)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)

.PHONY: install uninstall clean
