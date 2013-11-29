# *-* makefile *-*
CC=clang
CXX=clang++
OPT_FLAGS += -g
OPT_FLAGS += -O3
OPT_FLAGS += -Wall
CFLAGS += $(OPT_FLAGS)
CXXFLAGS += $(OPT_FLAGS)
CPP_DEP_FLAGS += -MM -MF $@.d
CPPFLAGS += -I.. -I/opt/local/include

CC_FILES := $(shell ls *.cc 2>/dev/null)
C_FILES  := $(shell ls *.c  2>/dev/null)

O_FILES = \
	$(CC_FILES:.cc=.o) \
	$(C_FILES:.c=.o)

T_CC_FILES := $(shell ls t/*.cc 2>/dev/null)
T_C_FILES  := $(shell ls t/*.c  2>/dev/null)
T_FILES = \
	$(T_CC_FILES:.cc=) \
	$(T_C_FILES:.c=)

TOOL_CC_FILES := $(shell ls tool/*.cc 2>/dev/null)
TOOL_C_FILES  := $(shell ls tool/*.c  2>/dev/null)
TOOL_FILES = \
	$(TOOL_CC_FILES:.cc=) \
	$(TOOL_C_FILES:.c=)

D_FILES = \
  $(O_FILES:=.d) \
  $(T_FILES:=.d)

.c.o:
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(COMPILE.c) $(OUTPUT_OPTION) $(CPP_DEP_FLAGS) $<
	sed -i -e 's@:@::@g' $@.d

.cc.o:
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(COMPILE.cc) $(OUTPUT_OPTION) $(CPP_DEP_FLAGS) $<
	sed -ie 's@:@::@g' $@.d

all : $(TOOL_FILES) $(LIB_A) $(T_FILES)

$(TOOL_FILES) : LDLIBS =

$(LIB_A) : $(O_FILES)
	ar -rs $@ $(O_FILES)
	rm -f $(T_FILES)

GARBAGE=
clean:
	rm -f *.o *.a $(T_FILES) $(D_FILES) $(TOOL_FILES) $(GARBAGE)

clean-tests:
	rm -f $(T_FILES)

-include $(D_FILES)

