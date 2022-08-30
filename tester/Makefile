.DEFAULT_GOAL = all

NAME = test_serialize

CXX = c++
CXXFLAGS ?= -Wall -Wextra -Werror -std=c++98

DIR_SRC = tests
DIR_INCLUDE ?= ../srcs
namespace ?= std
DIR_EXEC = .exec

INCLUDE = -I$(DIR_INCLUDE)

$(DIR_EXEC):
	mkdir -p $@

###VECTOR###

TEST = ../srcs/vector.hpp
SRC_VECTOR = $(wildcard $(DIR_SRC)/*/*.cpp)
EXEC_VECTOR = $(addprefix $(DIR_EXEC_VECTOR)/, $(notdir $(SRC_VECTOR:.cpp=)))
DIR_EXEC_VECTOR = $(DIR_EXEC)/$(namespace)_vector

$(DIR_EXEC_VECTOR)/% : $(DIR_SRC)/vector/%.cpp $(TEST)
	$(CXX) $(CXXFLAGS) $< $(INCLUDE) -D NAMESPACE=$(namespace) -o $@

$(DIR_EXEC_VECTOR): $(DIR_EXEC)
	@ mkdir -p $@

vector: $(DIR_EXEC_VECTOR) $(EXEC_VECTOR)

###VECTOR###


all: vector

clean:
	rm -f $(EXEC_VECTOR)

fclean: clean
	rm -rf $(DIR_EXEC_VECTOR)
	rm -rf $(DIR_EXEC)

re: fclean all

.PHONY: all clean fclean re
