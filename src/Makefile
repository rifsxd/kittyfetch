# Makefile for Kittyfetch C project

# Source file
SRC = kittyfetch.c

# Binary file
BIN = kittyfetch

# Base location
PREFIX ?= /usr/

# Flags
FLAG = -lX11

ICONS = "-D ICONS"

# Binary Folder
INSTALLPATH = ${DESTDIR}${PREFIX}/bin

# Compiler
CC = gcc

install : build

	@echo "installing binary file to ${INSTALLPATH}/${BIN}"
	@cp build/${BIN} ${INSTALLPATH}
	@chmod 0755 ${INSTALLPATH}/${BIN}
	@echo "installed"

install_icons : build_icons

	@echo "installing binary file to ${INSTALLPATH}/${BIN}"
	@cp build/${BIN} ${INSTALLPATH}
	@chmod 0755 ${INSTALLPATH}/${BIN}
	@echo "installed"

# Clean build files
clean:
	rm -rf build

# Build the project
build:
	mkdir build
	$(CC) -o build/$(BIN) $(SRC) $(FLAG)

# Build the project with icons
build_icons:
	mkdir build
	$(CC) -o build/$(BIN) $(SRC) $(ICONS) $(FLAG)

# Run the project
run: build
	./$(BIN)
