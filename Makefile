TEST_C   = $(sort $(wildcard tests/*.c)) # sort so that we execute these in order
TEST_OBJ = $(patsubst %.c,%.o,$(TEST_C))
TEST_BIN = $(patsubst %.c,%.bin,$(TEST_C))
TEST_DEP = $(patsubst %.c,%.d,$(TEST_C))
IMPL_C   = $(wildcard *.c)
IMPL_OBJ = $(patsubst %.c,%.o,$(IMPL_C))
IMPL_DEP = $(patsubst %.c,%.d,$(IMPL_C))

UTIL     = util

CC       = gcc
CFLAGS   = -MP -MD -Wall -Wextra -Werror -g -I. -I./$(UTIL)
LD       = gcc
# We add the lazy specifier so the PLT enables ltrace to work
LDFLAGS  = -L. -Wl,-z,lazy -no-pie

all: $(UTIL) $(TEST_BIN)

%.bin: %.o $(IMPL_OBJ)
	$(LD) $(LDFLAGS) $(IMPL_OBJ) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(TEST_OBJ) $(TEST_BIN) $(IMPL_OBJ) $(IMPL_DEP) $(TEST_DEP)

$(UTIL):
	wget https://github.com/gwu-cs-sysprog/utils/raw/main/util.tgz
	tar zxvf util.tgz
	rm util.tgz

test: $(UTIL) $(TEST_BIN)
	@echo "Running tests..."
	$(foreach T, $(TEST_BIN), ./$(T);)
	@echo "\nRunning valgrind (note: the last, fuzz test will take around a minute)..."
	$(foreach T, $(TEST_BIN), sh util/valgrind_test.sh ./$(T);)
	@echo "\nRunning the symbol visibility test..."
	sh util/assess_visibility.sh "kv_create\|kv_destroy\|kv_get\|kv_put" kv.o

.PHONY: all clean test

# include the dependencies
-include $(TEST_DEP) $(IMPL_DEP)
