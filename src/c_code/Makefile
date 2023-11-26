# Makefile for Kittyfetch C project

# Source file
SRC = kittyfetch.c

# Source file
SRC_TEST = kittyfetch_test.cpp

# Binary file
BIN = kittyfetch

# Binary file
BIN_TEST = kittyfetch_test

# Base location
PREFIX ?= /usr/

# Flags
FLAG = -lX11

LEGACY = "-D LEGACY"

# Binary Folder
INSTALLPATH = ${DESTDIR}${PREFIX}/bin

# Compiler
CC = gcc

CXX = g++

install : build

	@echo "installing binary file to ${INSTALLPATH}/${BIN}"
	@cp build/${BIN} ${INSTALLPATH}
	@chmod 0755 ${INSTALLPATH}/${BIN}
	@echo "installed"

install_legacy : build_legacy

	@echo "installing binary file to ${INSTALLPATH}/${BIN}"
	@cp build/${BIN} ${INSTALLPATH}
	@chmod 0755 ${INSTALLPATH}/${BIN}
	@echo "installed"

install_test : build_test

	@echo "installing binary file to ${INSTALLPATH}/${BIN_TEST}"
	@cp build/${BIN_TEST} ${INSTALLPATH}
	@chmod 0755 ${INSTALLPATH}/${BIN}
	@echo "installed"

install_test_legacy : build_test_legacy

	@echo "installing binary file to ${INSTALLPATH}/${BIN_TEST}"
	@cp build/${BIN_TEST} ${INSTALLPATH}
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
build_legacy:
	mkdir build
	$(CC) -o build/$(BIN) $(SRC) $(LEGACY) $(FLAG)

build_test:
	mkdir build
	$(CXX) -o build/$(BIN_TEST) $(SRC_TEST) $(FLAG)

build_test_legacy:
	mkdir build
	$(CXX) -o build/$(BIN_TEST) $(SRC_TEST) $(LEGACY) $(FLAG)

# Run the project
run: build
	./$(BIN)
