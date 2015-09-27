#--------------------------------------------------------
# system
#--------------------------------------------------------
UNAME = $(shell uname)

#--------------------------------------------------------
# target
#--------------------------------------------------------
TARGET = portugol

#--------------------------------------------------------
# directories
#--------------------------------------------------------
SRC_DIR   = ./src/
INC_DIR   = ./include/
INT_DIR   = .
LEX_DIR   = ./lex/
BIN_DIR   = ./bin/
OBJ_DIR   = ./obj/$(UNAME)/

#--------------------------------------------------------
# compilation configuration
#--------------------------------------------------------
CXX       = gcc
INCLUDE   = -I$(INT_DIR) -I$(INC_DIR)
LFLAGS    = 
CFLAGS    = -g -MD -MP -Wall -Werror -pedantic -std=c99
CLEXFLAGS = -g -Wall -Werror -pedantic -std=c99 -D_POSIX_SOURCE

#--------------------------------------------------------
# sources
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
else
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES = $(call rwildcard,$(SRC_DIR),*.c)
endif

#--------------------------------------------------------
# objects ans dependencies
#--------------------------------------------------------
OBJECTS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SOURCES))
DEPS    = $(OBJECTS:.o=.d)

#--------------------------------------------------------
# make all rule
#--------------------------------------------------------
all: portugol

#--------------------------------------------------------
# portugol rules
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
portugol: $(BIN_DIR)$(TARGET)
else
portugol: $(BIN_DIR)$(TARGET).exe
endif


#--------------------------------------------------------
# cleaning rule
#--------------------------------------------------------
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LEX_DIR)parser.c
	rm -rf $(LEX_DIR)parser.h
	rm -rf $(LEX_DIR)tokens.c
ifeq ($(UNAME), Linux)
	rm -rf $(BIN_DIR)$(TARGET)
else
	rm -rf $(BIN_DIR)$(TARGET).exe
endif


#--------------------------------------------------------
# hypnos objects and target rules
#--------------------------------------------------------

$(BIN_DIR)$(TARGET): $(OBJ_DIR)lex/parser.o $(OBJ_DIR)lex/tokens.o $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS) $(LFLAGS)
$(BIN_DIR)$(TARGET).exe: $(OBJ_DIR)lex/parser.o $(OBJ_DIR)lex/tokens.o $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS) $(LFLAGS)

-include $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $@

$(OBJ_DIR)lex/parser.o: $(LEX_DIR)parser.c
	@mkdir -p $(@D)
	$(CXX) -c $(CLEXFLAGS) $(INCLUDE) $< -o $@

$(LEX_DIR)parser.c: $(LEX_DIR)portugol.y
	bison -d -o $@ $^

$(LEX_DIR)parser.h: $(LEX_DIR)parser.c

$(OBJ_DIR)lex/tokens.o: $(LEX_DIR)tokens.c
	@mkdir -p $(@D)
	$(CXX) -c $(CLEXFLAGS) $(INCLUDE) $< -o $@

$(LEX_DIR)tokens.c: $(LEX_DIR)portugol.l $(LEX_DIR)parser.h
	flex -o $@ $^
