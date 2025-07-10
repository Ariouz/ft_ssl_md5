SRCS= $(addprefix srcs/, \
	ft_ssl.c \
	utils/error_handler.c \
	)
OBJS= $(SRCS:.c=.o)

NAME= ft_ssl
FLAGS= -Wall -Werror -Wextra
INCLUDES= -Iincludes/

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(FLAGS) $(OBJS) -o $(NAME)

bonus: FLAGS += -DBONUS
bonus: fclean $(NAME)

%.o: %.c
	@gcc -c $< -o $@ $(FLAGS) $(INCLUDES)

clean:
	@rm $(OBJS)

fclean: clean
	@rm $(NAME)

re: fclean all
