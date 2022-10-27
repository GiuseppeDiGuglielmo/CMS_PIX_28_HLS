#### BE CAREFUL: You may not need to edit this Makefile. ####

ifndef V
	QUIET_AR            = @echo 'MAKE:' AR $@;
	QUIET_BUILD         = @echo 'MAKE:' BUILD $@;
	QUIET_C             = @echo 'MAKE:' CC $@;
	QUIET_CXX           = @echo 'MAKE:' CXX $@;
	QUIET_CHECKPATCH    = @echo 'MAKE:' CHECKPATCH $(subst .o,.cpp,$@);
	QUIET_CHECK         = @echo 'MAKE:' CHECK $(subst .o,.cpp,$@);
	QUIET_LINK          = @echo 'MAKE:' LINK $@;
	QUIET_CP            = @echo 'MAKE:' CP $@;
	QUIET_MKDIR         = @echo 'MAKE:' MKDIR $@;
	QUIET_MAKE          = @echo 'MAKE:' MAKE $@;
	QUIET_INFO          = @echo -n 'MAKE:' INFO '';
	QUIET_RUN           = @echo 'MAKE:' RUN '';
	QUIET_CLEAN         = @echo 'MAKE:' CLEAN ${PWD};
endif

help:
	@echo "INFO: make <TAB> for targets"
.PHONY: help

TARGET := $(MODEL).x

CXX          = g++
TARGET_ARCH = linux64

INCDIR :=
INCDIR += -I$(MODEL_DIR)
INCDIR += -I$(MODEL_DIR)/inc
INCDIR += -I$(MODEL_DIR)/src
INCDIR += -I$(MODEL_DIR)/weights
INCDIR += -I$(SYSTEMC)/include

CXX_FLAGS :=
CXX_FLAGS += -MMD
CXX_FLAGS += -Wall
CXX_FLAGS += -Wno-int-in-bool-context
CXX_FLAGS += -Wno-uninitialized
CXX_FLAGS += -Wno-unknown-pragmas
CXX_FLAGS += -Wno-unused-label
CXX_FLAGS += -Wno-sign-compare
CXX_FLAGS += -Wno-unused-variable
CXX_FLAGS += -Wno-narrowing
CXX_FLAGS += -std=c++11
CXX_FLAGS += -O3
CXX_FLAGS += -DV05

# Define the following MACROs to load weights/biases from file.
#WEIGHTS_DIR := ./inputs/weights
#CXX_FLAGS += -D__WEIGHTS_DIR__=$(WEIGHTS_DIR)
#CXX_FLAGS += -D__WEIGHTS_FROM_FILE__

LD_FLAGS :=
LD_FLAGS += -lm
LD_FLAGS += -lpthread

LD_LIBS :=
LD_LIBS += -L$(SYSTEMC)/lib

VPATH :=
VPATH += $(MODEL_DIR)/tb
VPATH += $(MODEL_DIR)/inc
VPATH += $(MODEL_DIR)/src
VPATH += $(MODEL_DIR)/weights

#VPATH += ../$(MODEL_DIR)/nnet_utils

CXX_SOURCES :=
CXX_SOURCES += $(subst $(MODEL_DIR)/tb/,,$(wildcard $(MODEL_DIR)/tb/*.cpp))
CXX_SOURCES += $(subst $(MODEL_DIR)/src/,,$(wildcard $(MODEL_DIR)/src/*.cpp))

.SUFFIXES: .cpp .h .o

CXX_OBJECTS := $(CXX_SOURCES:.cpp=.o)
-include $(CXX_OBJECTS:.o=.d)

all: $(TARGET)

$(TARGET): $(CXX_OBJECTS)
	$(QUIET_LINK)$(CXX) -o $@ $(CXX_OBJECTS) ${LD_LIBS} ${LD_FLAGS}

.cpp.o:
	$(QUIET_CXX)$(CXX) $(CXX_FLAGS) ${INCDIR} -c $<

run: all
	$(QUIET_RUN)set -o pipefail; ./$(TARGET) | tee run-catapult.log
.PHONY: run

#valgrind:
#	$(QUIET_RUN)valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)
#.PHONY: valgrind

#gdb:
#	$(QUIET_RUN)gdb ./$(TARGET)
#.PHONY: gdb

clean:
	$(QUIET_CLEAN)rm -rf $(TARGET) *.o *.d
.PHONY: clean

ultraclean: clean
	$(QUIET_CLEAN)rm -rf ./tb_data/*.log *.log *.png ./tb_data/*.mem
.PHONY: ultraclean
