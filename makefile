SOURCE_DIR := libvivo libcore test

export CFLAGS = -O -g -Wall -DVIVO_DEBUG
export CC = g++
export JAVAC = javac
export DX = dx
export OUT_DIR = $(abspath out)/
export LIBDIR = $(OUT_DIR)/lib/

MAKE = make

.PHONY: all

all : 
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OUT_DIR)/lib
	@mkdir -p $(OUT_DIR)/bin
	@mkdir -p $(OUT_DIR)/javalib
	echo $(LIBDIR)
	@for DIR in $(SOURCE_DIR); do $(MAKE) -C $$DIR all || exit 1; done 
	
clean:
	rm -rf out/lib/*
