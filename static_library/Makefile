INC = include
OBJ = obj
SRC = src
LIB = lib
BIN = target

CC = gcc
CFLAGS = -I $(INC) -Wall

TARGETS = $(LIB)/libmymath.a $(BIN)/example


###########################################################
# Main
###########################################################

.PHONY: all
all: $(BIN)/example
	@printf "To run all samples:\n\n"
	@printf "    make run\n"


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

###########################################################
# Main
###########################################################

$(BIN)/%: usage/%.c $(LIB)/libmymath.a $(BIN)/.stamp
	$(CC) $(CFLAGS) -L $(LIB) -l mymath $< -o $@


###########################################################
# Common
###########################################################

.PHONY: run
run: $(BIN)/example
	$<

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN) $(LIB)


###########################################################
# Directories
###########################################################

%/.stamp:
	mkdir -p $(shell dirname $@)
	touch $@

.PRECIOUS: %/.stamp