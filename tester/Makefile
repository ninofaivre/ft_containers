### GLOBAL ###

.DEFAULT_GOAL = all

CXX = c++
CXXFLAGS ?= -Wall -Wextra -Werror -std=c++98

DIR_SRC = ./tests
DIR_OUTPUTS = ./outputs
DIR_INCLUDE ?= ../srcs
namespace ?= std
DIR_EXEC = ./.exec

INCLUDE = -I$(DIR_INCLUDE)

$(DIR_EXEC)/%:
	mkdir -p $@

$(DIR_OUTPUTS)/%:
	mkdir -p $@

### GLOBAL ###

### VECTOR ###

SRC_VECTOR = $(wildcard $(DIR_SRC)/*/*.cpp)
EXEC_VECTOR = $(addprefix $(DIR_EXEC)/$(namespace)_vector/, $(notdir $(SRC_VECTOR:.cpp=)))
DIR_VECTOR = $(DIR_EXEC)/$(namespace)_vector $(DIR_OUTPUTS)/$(namespace)_vector

$(DIR_EXEC)/$(namespace)_vector/% : $(DIR_SRC)/vector/%.cpp
	- $(CXX) $(CXXFLAGS) $< $(INCLUDE) -D NAMESPACE=$(namespace) -o $@\
		2> $(DIR_OUTPUTS)/$(namespace)_vector/$(notdir $@).output

$$(DIR_VECTOR):

vector: $(DIR_VECTOR) $(EXEC_VECTOR)

### VECTOR ###

### BASE ###

all: vector

clean:
	rm -f $(DIR_OUTPUTS)/*/*.output

fclean: clean
	$(eval namespace=std)
	rm -rf $(EXEC_VECTOR)
	rm -rf $(DIR_VECTOR)
	$(eval namespace=ft)
	rm -rf $(EXEC_VECTOR)
	rm -rf $(DIR_VECTOR)
	# not namespace related :
	rm -rf $(DIR_EXEC)
	rm -rf $(DIR_OUTPUTS)

re: fclean all

.PHONY: all clean fclean re

### BASE ###
