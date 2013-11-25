CC=clang
CXX=clang++
CFLAGS += -g
CFLAGS += -O3
CINCLUDES+=-I.. -I/opt/local/include
CFLAGS += $(CINCLUDES)
CXXFLAGS += $(CINCLUDES)

CC_FILES := $(shell ls *.cc)
C_FILES  := $(shell ls *.c)

O_FILES = \
	$(CC_FILES:.cc=.o) \
	$(C_FILES:.c=.o)

T_CC_FILES := $(shell ls t/*.cc)
T_C_FILES  := $(shell ls t/*.c)
T_FILES = \
	$(T_CC_FILES:.cc=) \
	$(T_C_FILES:.c=)

all : $(LIB_A) $(T_FILES)

$(LIB_A) : $(O_FILES)
	ar -r $@ $(O_FILES)

clean:
	rm -f *.o *.a $(T_FILES)

