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

TEST_FILE   ?= aq_test.c
TEST_SOURCES = $(TEST_FILE) aux.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

DEMO_EXECUTABLE = demo
TEST_EXECUTABLE = test

EXECUTABLES = $(DEMO_EXECUTABLE) $(TEST_EXECUTABLE)

.PHONY:  all lib lib-seq clean clean-all

all: lib lib-seq demo test  

lib-seq: $(LIB_DIR)/$(LIB_SEQ_NAME)
 
lib: $(LIB_DIR)/$(LIB_NAME)

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

$(TEST_EXECUTABLE): lib $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -lpthread -L$(LIB_DIR) -l$(LIB) -o $@ 

clean:
	rm -rf *.o *~ 

clean-all: clean
	rm -rf $(LIB_DIR) $(EXECUTABLES)

