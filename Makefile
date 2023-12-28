NAME = NeuralNetwork

# Directory for object files
OBJDIR = obj

# Sources
SRCS = $(addprefix src/, main.cpp NeuralNetwork.cpp Layer.cpp Neuron.cpp Connection.cpp ActivationFunction.cpp utils.cpp Data.cpp Cost.cpp)

# Object files
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Compiler flags
CFLAGS = -g -Wall -Wextra -Werror
CC = g++
RM = rm -f

# Create object directory if it does not exist
create_obj_dir:
	@mkdir -p $(OBJDIR)

# Rule for object files
$(OBJDIR)/%.o: src/%.cpp | create_obj_dir
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -fsanitize=address -o $(NAME)

# Standard rules
all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re create_obj_dir
