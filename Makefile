#--------------------------------------------------------
# system
#--------------------------------------------------------
UNAME = $(shell uname)

#--------------------------------------------------------
# target
#--------------------------------------------------------
TARGET = portugol_plus

#--------------------------------------------------------
# directories
#--------------------------------------------------------
SRC_DIR = ./src/
INC_DIR = ./include/
INT_DIR = .

BIN32_DIR = ./bin32/
BIN64_DIR = ./bin64/

OBJ_DIR = ./obj/$(UNAME)/
OBJ32_DIR = $(OBJ_DIR)32bit/
OBJ64_DIR = $(OBJ_DIR)64bit/

ifneq ($(UNAME), Linux)
SDL_DIR   = E:/SDL2/
SDL32_DIR = $(SDL_DIR)i686-w64-mingw32/
SDL64_DIR = $(SDL_DIR)x86_64-w64-mingw32/
endif

HYP_DIR   = ../hypnos-cpp/

#--------------------------------------------------------
# compilation configuration
#--------------------------------------------------------
CXX = g++

ifeq ($(UNAME), Linux)
INCLUDE   = -I$(INT_DIR) -I$(INC_DIR) -I$(HYP_DIR)include
LFLAGS32  = -lrt -lm -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -L$(HYP_DIR)bin -lhypnos.l32
LFLAGS64  = -lrt -lm -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -L$(HYP_DIR)bin -lhypnos.l64
else
INCLUDE32 = -I$(INT_DIR) -I$(INC_DIR) -I$(SDL32_DIR)include/ -I$(HYP_DIR)include
INCLUDE64 = -I$(INT_DIR) -I$(INC_DIR) -I$(SDL64_DIR)include/ -I$(HYP_DIR)include
LFLAGS32  = -L$(SDL32_DIR)lib/ -lm -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -L$(HYP_DIR)bin -lhypnos.w32
LFLAGS64  = -L$(SDL64_DIR)lib/ -lm -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -L$(HYP_DIR)bin -lhypnos.w64
endif

ifeq ($(UNAME), Linux)
CFLAGS    = -MD -MP -Wall -Werror -pedantic -std=c++11 -O2 -fPIC
else
CFLAGS    = -MD -MP -Wall -Werror -pedantic -std=c++11 -O2
endif
CFLAGS32  = -m32 $(CFLAGS)
CFLAGS64  = -m64 $(CFLAGS)

#--------------------------------------------------------
# sources
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
else
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES = $(call rwildcard,$(SRC_DIR),*.cpp)
endif

#--------------------------------------------------------
# objects ans dependencies
#--------------------------------------------------------
OBJECTS32 = $(patsubst $(SRC_DIR)%.cpp, $(OBJ32_DIR)%.o, $(SOURCES))
OBJECTS64 = $(patsubst $(SRC_DIR)%.cpp, $(OBJ64_DIR)%.o, $(SOURCES))

DEPS32	= $(OBJECTS32:.o=.d)
DEPS64	= $(OBJECTS64:.o=.d)

#--------------------------------------------------------
# make all rule
#--------------------------------------------------------
all: skeleton64

#--------------------------------------------------------
# exec rules
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
skeleton32: $(BIN32_DIR)$(TARGET).l32
skeleton64: $(BIN64_DIR)$(TARGET).l64
else
skeleton32: $(BIN32_DIR)$(TARGET).w32.exe
skeleton64: $(BIN64_DIR)$(TARGET).w64.exe
endif

#--------------------------------------------------------
# cleaning rule
#--------------------------------------------------------
clean:
	rm -rf $(OBJ32_DIR)
	rm -rf $(OBJ64_DIR)
ifeq ($(UNAME), Linux)
	rm -rf $(BIN32_DIR)$(TARGET).l32
	rm -rf $(BIN64_DIR)$(TARGET).l64
else
	rm -rf $(BIN32_DIR)$(TARGET).w32.exe
	rm -rf $(BIN64_DIR)$(TARGET).w64.exe
endif

#--------------------------------------------------------
# objects and target rules
#--------------------------------------------------------

ifeq ($(UNAME), Linux)
$(BIN32_DIR)$(TARGET).l32: $(OBJECTS32)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS32) $(LFLAGS32)
$(BIN64_DIR)$(TARGET).l64: $(OBJECTS64)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS64) $(LFLAGS64)
else
$(BIN32_DIR)$(TARGET).w32.exe: $(OBJECTS32)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS32) $(LFLAGS32)
	cp $(HYP_DIR)bin/libhypnos.w32.dll $(BIN32_DIR)
$(BIN64_DIR)$(TARGET).w64.exe: $(OBJECTS64)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS64) $(LFLAGS64)
	cp $(HYP_DIR)bin/libhypnos.w64.dll $(BIN64_DIR)
endif

-include $(DEPS32)
-include $(DEPS64)

ifeq ($(UNAME), Linux)
$(OBJ32_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS32) $(INCLUDE) $< -o $@
else
$(OBJ32_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS32) $(INCLUDE32) $< -o $@
endif

ifeq ($(UNAME), Linux)
$(OBJ64_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS64) $(INCLUDE) $< -o $@
else
$(OBJ64_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS64) $(INCLUDE64) $< -o $@
endif
