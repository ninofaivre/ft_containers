### GLOBAL ###

.DEFAULT_GOAL = all

CXX ?= c++
CXXFLAGS ?= -Wall -Wextra -Werror -std=c++98

DIR_SRC = ./tests
DIR_OUTPUTS = ./outputs
DIR_CONTAINERS ?= ../srcs
namespace ?= std
STD := $(if $(filter $(namespace), std),1,0)
FT := $(if $(filter $(namespace), ft),1,0)
DIR_EXEC = ./.exec

DEFINE = -D NAMESPACE=$(namespace) -D FT=$(FT) -D STD=$(STD)
INCLUDE = -I$(DIR_CONTAINERS)

$(DIR_EXEC)/%:
	mkdir -p $@

$(DIR_OUTPUTS)/%:
	mkdir -p $@

### GLOBAL ###

### VECTOR ###

VecDirName = $(namespace)_vector
VecSrc = $(wildcard $(DIR_SRC)/vector/*.cpp)
VecExec = $(addprefix $(DIR_EXEC)/$(VecDirName)/, $(notdir $(VecSrc:.cpp=)))
VecDir = $(DIR_EXEC)/$(VecDirName) $(DIR_OUTPUTS)/$(VecDirName)

$(DIR_EXEC)/$(VecDirName)/% : $(DIR_SRC)/vector/%.cpp
	- $(CXX) $(CXXFLAGS) $< $(INCLUDE) $(DEFINE) -o $@\
		2> $(DIR_OUTPUTS)/$(VecDirName)/$(notdir $@).output

$$(VecDir):

vector: $(VecDir) $(VecExec)

### VECTOR ###

### STACK ###

StackDirName = $(namespace)_stack
StackSrc = $(wildcard $(DIR_SRC)/stack/*.cpp)
StackExec = $(addprefix $(DIR_EXEC)/$(StackDirName)/, $(notdir $(StackSrc:.cpp=)))
StackDir = $(DIR_EXEC)/$(StackDirName) $(DIR_OUTPUTS)/$(StackDirName)

$(DIR_EXEC)/$(StackDirName)/% : $(DIR_SRC)/stack/%.cpp
	- $(CXX) $(CXXFLAGS) $< $(INCLUDE) $(DEFINE) -o $@\
		2> $(DIR_OUTPUTS)/$(StackDirName)/$(notdir $@).output

$$(StackDir):

stack: $(StackDir) $(StackExec)

### STACK ###

### MAP ###

MapDirName = $(namespace)_map
MapSrc = $(wildcard $(DIR_SRC)/map/*.cpp)
MapExec = $(addprefix $(DIR_EXEC)/$(MapDirName)/, $(notdir $(MapSrc:.cpp=)))
MapDir = $(DIR_EXEC)/$(MapDirName) $(DIR_OUTPUTS)/$(MapDirName)

$(DIR_EXEC)/$(MapDirName)/% : $(DIR_SRC)/map/%.cpp
	- $(CXX) $(CXXFLAGS) $< $(INCLUDE) $(DEFINE) -o $@\
		2> $(DIR_OUTPUTS)/$(MapDirName)/$(notdir $@).output

$$(MapDir):

map: $(MapDir) $(MapExec)

### MAP ###

### BASE ###

all: vector stack map

softClean:
	@rm -f $(DIR_OUTPUTS)/$(VecDirName)/*.output
	@rm -f $(DIR_OUTPUTS)/$(StackDirName)/*.output
	@rm -f $(DIR_OUTPUTS)/$(MapDirName)/*.output
	@echo "deleting $(DIR_OUTPUTS)/$(namespace)_{containers}/*.output"

clean: softClean
	@rm -f $(VecExec)
	@rm -f $(StackExec)
	@rm -f $(MapExec)
	@echo "deleting $(DIR_EXEC)/$(namespace)_{containers}/{tests_names}"

fclean: clean
	rm -rf $(VecDir)
	rm -rf $(StackDir)
	rm -rf $(MapDir)
	rm -rf $(DIR_EXEC)
	rm -rf $(DIR_OUTPUTS)

re: clean all

.PHONY: all vector stack map softClean clean fclean re

### BASE ###
