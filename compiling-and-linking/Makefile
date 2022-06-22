INC = include
OBJ = obj
SRC = src
TARGET = target

CC = gcc
CFLAGS=-I $(INC) -Wall


###########################################################
# Common Definitions
###########################################################

TARGETS=$(TARGET)/standalone $(TARGET)/sample-with-deps


###########################################################
# Common
###########################################################

.PHONY: all
all: $(TARGETS)
	@printf "To run all samples:\n\n"
	@printf "    make run\n"

TARGETSTAMP=$(TARGET)/.stamp
$(TARGETSTAMP):
	mkdir -p $(TARGET)
	touch $@

OBJSTAMP=$(OBJ)/.stamp
$(OBJSTAMP):
	mkdir -p $(OBJ)
	touch $@

.PHONY: run
run: $(TARGETS)
	$(TARGET)/standalone
	$(TARGET)/sample-with-deps

.PHONY: clean
clean:
	rm -rf $(OBJ)
	rm -rf $(TARGET)


###########################################################
# Standalone from single file
###########################################################

$(TARGET)/standalone: $(SRC)/standalone.c $(TARGETSTAMP)
	$(CC) $< -o $@


###########################################################
# Standalone from multiple files compile+link separated
###########################################################

_DEPS = plus.h
_OBJS = sample-with-deps.o plus.o

DEPS = $(patsubst %,$(INC)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ)/%,$(_OBJS))

$(OBJ)/%.o: $(SRC)/%.c $(DEPS) $(OBJSTAMP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET)/sample-with-deps: $(OBJS) $(TARGETSTAMP)
	$(CC) -lc -o $@ $(OBJS)
