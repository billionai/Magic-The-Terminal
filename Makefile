CC = g++
COMP_FLAGS = -Wall -c -O2
LINK_FLAGS = #change once we actually need link flags
DEBUG_FLAGS = -O0 -g3 -DDEBUG_BUILD
OUTPUT = mtt
OUTPUT_DEBUG = mtt.debug
SRC_FILES = $(wildcard src/*.cc)
HEADER_FILES = $(wildcard src/*.h)
OBJ_FILES = $(SRC_FILES:.cc=.o)
SRC_DEPS = $(SRC_FILES:.cc=.d)

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES)
	$(CC) $(LINK_FLAGS) -o $(OUTPUT) $(OBJ_FILES)

-include $(SRC_DEPS)

# the move, sed and rm commands setup the .d file to have the rule name
# start with "src/", otherwise the rules wont work
%.o:%.cc
	$(CC) $(COMP_FLAGS) $< -o $@
	$(CC) $(COMP_FLAGS) -MM $< -o $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp >$*.d
	@rm -f $*.d.tmp

debug:
	$(CC) $(DEBUG_FLAGS) $(SRC_FILES) -o $(OUTPUT_DEBUG)
	gdb ./$(OUTPUT_DEBUG) -q

clean:
	rm $(OBJ_FILES) $(OUTPUT)
