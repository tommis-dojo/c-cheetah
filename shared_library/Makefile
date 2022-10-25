INC = include
OBJ = obj
SRC = src
LIB = lib
BIN = target

CC = gcc
CFLAGS = -I $(INC) -Wall -Werror

MYLIB = mymath
LIBFILE = $(LIB)/lib$(MYLIB).so
EXE = $(BIN)/example
TARGETS = $(LIBFILE) $(EXE)


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
lib: $(LIBFILE)  # Build library

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
	SHOW_SHARED_LIBS = otool -L
else
	SHOW_SHARED_LIBS = ldd
endif


###########################################################
# Lib
###########################################################


O=$(OBJ)/minus.o $(OBJ)/plus.o
DEPS = include/mymath.h

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)/.stamp
	# pic: position independant code
	$(CC) $(CFLAGS) -fpic -c -o $@ $<

$(LIBFILE): $(O)
	mkdir -p $(LIB)
	gcc -shared -o $@ $^

###########################################################
# Main
###########################################################

$(BIN)/%: usage/%.c $(LIBFILE) $(BIN)/.stamp
	$(CC) $(CFLAGS) -L $(LIB) -l $(MYLIB) $< -o $@


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
show: $(TARGETS)  # Show symbols inside library and program
	@printf "\nSymbols inside $(LIBFILE):\n"
	nm $(LIBFILE)

	@printf "\nShared library inside $(EXE):\n"
	$(SHOW_SHARED_LIBS) $(EXE)

