INC = include
OBJ = obj
SRC = src
LIB = lib
BIN = target

CC = gcc
CFLAGS = -I $(INC) -Wall

MYLIB = $(LIB)/libmymath.a
TARGETS = $(MYLIB) $(BIN)/example


###########################################################
# Main
###########################################################

HELP_PATTERN = ^[a-zA-Z\-]*:.*\#.*
SUBST_PATTERN = ^\([a-zA-Z\-]*:\).*\#\(.*\)


.PHONY: help
help:
	@printf "Selected targets available:\n"
	@grep -E $(HELP_PATTERN) Makefile | sed "s/$(SUBST_PATTERN)/\t\1\t\2/"

.PHONY: lib
lib: $(MYLIB)  # Build library

.PHONY: build-all
build-all: $(BIN)/example  # Build library and example program

###########################################################
# Platform-Dependant
###########################################################

# Following: only for linux and macos
# May add windows when it touches me

UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	# MacOS with LD seems to be clunky
	LDFLAGS += -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -lSystem
endif


###########################################################
# Lib
###########################################################


O=$(OBJ)/minus.o $(OBJ)/plus.o
DEPS = include/mymath.h

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)/.stamp
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB)/libmymath.a: $(O)
	mkdir -p $(LIB)
	ar -rc $@ $^

	# Note: ranlib creates an index of all files inside the archive
	# It may or may not be necessary depending on platform.
	ranlib $(MYLIB)

###########################################################
# Main
###########################################################

$(BIN)/%: usage/%.c $(MYLIB) $(BIN)/.stamp
	$(CC) $(CFLAGS) -L $(LIB) -l mymath $< -o $@


###########################################################
# Common
###########################################################

.PHONY: run
run: $(BIN)/example	 # Run example program
	$<

.PHONY: clean
clean:  # Remove created files
	rm -rf $(OBJ) $(BIN) $(LIB)


###########################################################
# Directories
###########################################################

%/.stamp:
	mkdir -p $(shell dirname $@)
	touch $@

.PRECIOUS: %/.stamp

###########################################################
# Show
###########################################################

.PHONY: show
show: $(MYLIB)  # Show files and symbols inside library
	@printf "\nFiles inside $(MYLIB):\n"
	ar -t $(MYLIB)

	@printf "\nSymbols inside $(MYLIB):\n"
	nm $(MYLIB)
