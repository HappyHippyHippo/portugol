#--------------------------------------------------------
# system and target name
#--------------------------------------------------------
BITS           ?= 64
ENV            ?= debug
ARCH			= windows$(BITS)
TARGET          = portugol

FILE            = $(TARGET).exe

#--------------------------------------------------------
# directories
#--------------------------------------------------------
BASE_DIR        = ./

INC_DIR         = $(BASE_DIR)include/
BIN_DIR         = $(BASE_DIR)../bin/$(ARCH)-$(ENV)/
OBJ_DIR         = $(BASE_DIR)obj/$(ARCH)-$(ENV)/

LIB_DIR         = $(BASE_DIR)../libpt/

#--------------------------------------------------------
# compilation configuration
#--------------------------------------------------------
CC              = gcc
CFLAGS_STD      = -m$(BITS) -MD -MP -Wall -Werror -pedantic -std=c99 -fpic
LFLAGS          = -L$(BIN_DIR) -Wl,-rpath '-Wl,$$ORIGIN' -L$(LIB_DIR)$(BIN_DIR) -lpt
RM              = rm
ECHO            = echo

#--------------------------------------------------------
# compilation objects
#--------------------------------------------------------
APP_INCLUDE     = -I$(BASE_DIR) -I$(INC_DIR) -I$(LIB_DIR)include/
APP_SOURCES     = $(shell find -name '*.c')
APP_OBJECTS  	= $(patsubst %.c, $(OBJ_DIR)target/%.o, $(APP_SOURCES))
APP_DEPS     	= $(APP_OBJECTS:.o=.d)

ifeq ($(ENV), deploy)
	CFLAGS   	= -O3 $(CFLAGS_STD) -DNDEBUG
else
	CFLAGS    	= -g $(CFLAGS_STD)
endif

#--------------------------------------------------------
# target rules
#--------------------------------------------------------
all: lib
lib: $(BIN_DIR)$(FILE)

#--------------------------------------------------------
# dependencies
#--------------------------------------------------------
-include $(APP_DEPS)

#--------------------------------------------------------
# app deploy rules
#--------------------------------------------------------
$(BIN_DIR)$(FILE) : $(APP_OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ $(LFLAGS) 

$(OBJ_DIR)target/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(APP_INCLUDE) $< -o $@

#--------------------------------------------------------
# clean rule
#--------------------------------------------------------
clean :
	$(RM) -rf $(BIN_DIR)$(FILE)
	$(RM) -rf $(BASE_DIR)obj/
