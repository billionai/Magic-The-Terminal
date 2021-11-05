CC = g++
COMP_FLAGS = -Wall -c -O2
LINK_FLAGS = #change once we actually need link flags
DEBUG_FLAGS = -O0 -g3
OUTPUT = mtt
SRC_FILES = $(wildcard src/*.cc)
OBJ_FILES = $(SRC_FILES:.cc=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES)
	$(CC) $(LINK_FLAGS) -o $(OUTPUT) $(OBJ_FILES)

%.o:%.c
	$(CC) $(COMP_FLAGS) $<
