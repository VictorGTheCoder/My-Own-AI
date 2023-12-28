NAME = NeuralNetwork

# Sources
SRCS = main.cpp NeuralNetwork.cpp Layer.cpp Neuron.cpp Connection.cpp

OBJS = ${SRCS:.c=.o}

CFLAGS = -g -Wall -Wextra -Werror
CC = gcc
RM = rm -f


%.o: %.c
	$(CC) $(CFLAGS) ${INCL} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -fsanitize=address -o $(NAME)

all: ${NAME}

clean:
	$(RM) $(OBJS)

fclean: clean
	${RM} ${NAME}


re: fclean all

.PHONY: all clean fclean re
