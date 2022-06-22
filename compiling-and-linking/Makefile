CC=gcc


TARGETS=target/standalone

.PHONY: all
all: $(TARGETS)

###########################################################
# Standalone from single file
###########################################################

target/standalone: src/standalone.c
	mkdir -p target
	$(CC) $< -o $@

.PHONY: run
run: target/standalone
	$<

###########################################################
# Common
###########################################################

.PHONY: clean
clean:
	rm -f $(TARGETS)
