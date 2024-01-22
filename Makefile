NAME = NeuralNetwork

# Sources
SRCS = $(addprefix src/, main.cpp NeuralNetwork.cpp Layer.cpp Neuron.cpp Connection.cpp ActivationFunction.cpp utils.cpp Data.cpp Cost.cpp Draw.cpp MNIST.cpp)

# Object files - compiled objects will be in the same directory as the sources
OBJS = $(SRCS:.cpp=.o)

# Compiler flags
CFLAGS = -g -Wall -Wextra -Werror 
CC = g++
RM = rm -f

# Rule for object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -fsanitize=address -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system -I include/json/include/

# Standard rules
all: $(NAME)

clean:
	$(RM) $(SRCS:.cpp=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
