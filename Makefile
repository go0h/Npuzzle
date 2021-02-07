# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astripeb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/31 20:08:29 by astripeb          #+#    #+#              #
#    Updated: 2021/02/07 21:24:38 by astripeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN 			:= \033[0;32m
RED 			:= \033[0;31m
RESET			:= \033[0m

NAME			:= Npuzzle

SRC_DIR			:= ./src
INC_DIR			:= ./include
OBJ_DIR			:= ./obj

SRCS			:= Main.cpp Utils.cpp Node.cpp\
				NodeMove.cpp PuzzExcept.cpp ReadPuzzle.cpp\
				Manhattan.cpp LinearConflict.cpp OptimalH.cpp\
				AStarSearch.cpp IDAStarSearch.cpp GreedySearch.cpp\
				UniformCostSearch.cpp

OBJ				:= $(SRCS:.cpp=.o)

CXX				:= g++
CXXFLAGS		?= -Wall -Werror -Wextra -O3 #-std=c++17
IFLAGS			:= -I$(INC_DIR)
DEPEND			:= -MD -MT

vpath %.cpp		$(SRC_DIR)
vpath %.h		$(INC_DIR)
vpath %.o		$(OBJ_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(addprefix $(OBJ_DIR)/,$(OBJ)) -o $@
	echo "$(GREEN)$@ was created ✅$(RESET)"

$(OBJ):%.o:%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -o $(OBJ_DIR)/$@ -c $< $(DEPEND) $@
	echo "$(GREEN)$@ was created$(RESET)"

$(OBJ_DIR):
	mkdir -p $@

Debug:
	$(MAKE) CXXFLAGS="-g"

include $(wildcard $(OBJ_DIR)/*.d)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean
	$(MAKE) all

.SILENT: all clean fclean re $(NAME) $(OBJ_DIR) $(OBJ) Debug

.PHONY: clean fclean re all Debug
