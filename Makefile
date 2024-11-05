CC = gcc

CCWARNINGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable \
  -Wno-unused-function
CCOPTS     = -g -O0

CFLAGS = $(CCWARNINGS) $(CCOPTS)

LIB_SOURCES = aq_tsafe.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
LIB         = aq
LIB_DIR     = mylib
LIB_NAME     = lib$(LIB).a

LIB_SEQ_SOURCES = aq_seq.c
LIB_SEQ_OBJECTS = $(LIB_SEQ_SOURCES:.c=.o)
LIB_SEQ         = aq_seq
LIB_SEQ_NAME    = lib$(LIB_SEQ).a

DEMO_SOURCES = aq_demo.c aux.c
DEMO_OBJECTS = $(DEMO_SOURCES:.c=.o)
DEMO_EXECUTABLE = demo

TEST_FILE  = aq_test.c
TEST_FILE1  = test_file1.c
TEST_FILE2  = test_file2.c
TEST_FILE3  = test_file3.c

TEST_SOURCES = $(TEST_FILE) $(TEST_FILE1) $(TEST_FILE2) $(TEST_FILE3) aux.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

TEST_EXECUTABLE = aq_test
TEST_EXECUTABLE1 = test_file1
TEST_EXECUTABLE2 = test_file2
TEST_EXECUTABLE3 = test_file3

EXECUTABLES = $(DEMO_EXECUTABLE) $(TEST_EXECUTABLE) $(TEST_EXECUTABLE1) $(TEST_EXECUTABLE2) $(TEST_EXECUTABLE3)

.PHONY:  all lib lib-seq demo test clean clean-all

all: lib lib-seq demo test

demo: $(DEMO_EXECUTABLE)

test: $(TEST_EXECUTABLE) $(TEST_EXECUTABLE1) $(TEST_EXECUTABLE2) $(TEST_EXECUTABLE3)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/$(LIB_NAME): $(LIB_OBJECTS)
	mkdir -p $(LIB_DIR)
	ar -rcs $@ $^

$(LIB_DIR)/$(LIB_SEQ_NAME): $(LIB_SEQ_OBJECTS)
	mkdir -p $(LIB_DIR)
	ar -rcs $@ $^

$(DEMO_EXECUTABLE): lib-seq $(DEMO_OBJECTS)
	$(CC) $(CFLAGS) $(DEMO_OBJECTS) -L$(LIB_DIR) -l$(LIB_SEQ) -o $@

$(TEST_EXECUTABLE): lib $(TEST_FILE:.c=.o) aux.o
	$(CC) $(CFLAGS) $(TEST_FILE:.c=.o) aux.o -lpthread -L$(LIB_DIR) -l$(LIB) -o $@

$(TEST_EXECUTABLE1): lib $(TEST_FILE1:.c=.o) aux.o
	$(CC) $(CFLAGS) $(TEST_FILE1:.c=.o) aux.o -lpthread -L$(LIB_DIR) -l$(LIB) -o $@

$(TEST_EXECUTABLE2): lib $(TEST_FILE2:.c=.o) aux.o
	$(CC) $(CFLAGS) $(TEST_FILE2:.c=.o) aux.o -lpthread -L$(LIB_DIR) -l$(LIB) -o $@

$(TEST_EXECUTABLE3): lib $(TEST_FILE3:.c=.o) aux.o
	$(CC) $(CFLAGS) $(TEST_FILE3:.c=.o) aux.o -lpthread -L$(LIB_DIR) -l$(LIB) -o $@

clean:
	rm -rf *.o *~

clean-all: clean
	rm -rf $(LIB_DIR) $(EXECUTABLES)