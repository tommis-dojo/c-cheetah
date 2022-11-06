IDIR = include
ODIR = obj
SDIR = src
TDIR = target

CC = gcc
CFLAGS = -I $(IDIR) -Wall

APPS = standalone sample-with-deps




###########################################################
# Platform-Dependant
###########################################################

# Following: only for linux and macos
# May add windows when it touches me

UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	# MacOS with LD seems to be clunky, but at least it works
	LDFLAGS += -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX12.1.sdk -lSystem
endif


###########################################################
# Common Definitions
###########################################################

LINKER_VARIANTS=LD GCC
TARGETS=$(TDIR)/GCC/standalone $(TDIR)/GCC/sample-with-deps 

ifeq ($(UNAME_S),Darwin)
TARGETS+=$(TDIR)/LD/sample-with-deps
endif

###########################################################
# Common
###########################################################

.PHONY: all
all: $(TARGETS)
	@printf "To run all samples:\n\n"
	@printf "    make run\n"

STAMPS = $(ODIR)/.stamp $(TDIR)/GCC/.stamp $(TDIR)/LD/.stamp
$(STAMPS):
	$(foreach stamp, $(STAMPS), mkdir -p $(shell dirname $(stamp)); touch $(stamp); )


.PHONY: run
run: $(TARGETS)
	$(foreach target, $(TARGETS), \
		$(target); \
	)

.PHONY: clean
clean:
	rm -rf $(ODIR)
	rm -rf $(TDIR)


###########################################################
# Standalone from single file in single gcc call
###########################################################

$(TDIR)/GCC/standalone: $(SDIR)/standalone.c $(STAMPS)
	$(CC) $< -o $@


###########################################################
# Standalone from multiple files compile+link separated
###########################################################

_DEPS = plus.h
_OBJS = sample-with-deps.o plus.o

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS) $(STAMPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TDIR)/GCC/sample-with-deps: $(OBJS) $(STAMPS)
	# Linking with GCC
	$(CC) -lc -o $@ $(OBJS)

ifeq ($(UNAME_S),Darwin)
	# MacOS linker works, but could not easily make it work with Linux.
	# Calling gcc with "-v" seems to output the linker options that gcc
	# calls ld with, but it seems to be unnecessarily complicated.
	# So skip ld with linux, for now.
	#
$(TDIR)/LD/sample-with-deps: $(OBJS) $(STAMPS)
	# Linking traditionally with LD
	ld $(LDFLAGS) $(OBJS) -o $@ 
endif
