CC = g++
COMP_FLAGS = -Wall -c -O2
LINK_FLAGS = #change once we actually need link flags
DEBUG_FLAGS = -O0 -g3 -DDEBUG_BUILD
OUTPUT = mtt
SRC_FILES = $(wildcard src/*.cc)
HEADER_FILES = $(wildcard src/*.h)
OBJ_FILES = $(SRC_FILES:.cc=.o)
SRC_DEPS = $(SRC_FILES:.cc=.d)

all: $(OUTPUT)

depend: .depend

.depend: $(SRC_FILES)
	$(CC) -MMD $^ -MF $@

include .depend

$(OUTPUT): $(OBJ_FILES) depend
	$(CC) $(LINK_FLAGS) -o $(OUTPUT) $(OBJ_FILES)

%.o:%.cc
	$(CC) $(COMP_FLAGS) $< -o $@

debug:
	$(CC) $(DEBUG_FLAGS) $(SRC_FILES) -o $(OUTPUT)

clean:
	rm $(OBJ_FILES) $(OUTPUT)
	rm core.*
