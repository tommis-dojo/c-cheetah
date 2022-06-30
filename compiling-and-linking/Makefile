INC = include
OBJ = obj
SRC = src
TARGET = target
APPS = standalone sample-with-deps

CC = gcc
CFLAGS=-I $(INC) -Wall


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
# Common Definitions
###########################################################

LINKER_VARIANTS=LD GCC
TARGETS=$(TARGET)/GCC/standalone $(TARGET)/GCC/sample-with-deps $(TARGET)/LD/sample-with-deps


###########################################################
# Common
###########################################################

.PHONY: all
all: $(TARGETS)
	@printf "To run all samples:\n\n"
	@printf "    make run\n"

STAMPS = $(OBJ)/.stamp $(TARGET)/GCC/.stamp $(TARGET)/LD/.stamp
$(STAMPS):
	$(foreach stamp, $(STAMPS), mkdir -p $(shell dirname $(stamp)); touch $(stamp); )


.PHONY: run
run: $(TARGETS)
	$(foreach target, $(TARGETS), \
		$(target); \
	)

.PHONY: clean
clean:
	rm -rf $(OBJ)
	rm -rf $(TARGET)


###########################################################
# Standalone from single file in single gcc call
###########################################################

$(TARGET)/GCC/standalone: $(SRC)/standalone.c $(STAMPS)
	$(CC) $< -o $@


###########################################################
# Standalone from multiple files compile+link separated
###########################################################

_DEPS = plus.h
_OBJS = sample-with-deps.o plus.o

DEPS = $(patsubst %,$(INC)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ)/%,$(_OBJS))

$(OBJ)/%.o: $(SRC)/%.c $(DEPS) $(STAMPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET)/GCC/sample-with-deps: $(OBJS) $(STAMPS)
	# Linking with GCC
	$(CC) -lc -o $@ $(OBJS)

$(TARGET)/LD/sample-with-deps: $(OBJS) $(STAMPS)
	# Linking traditionally with LD
	ld $(LDFLAGS) $(OBJS) -o $@ 

