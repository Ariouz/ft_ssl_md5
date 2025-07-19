SRCS= $(addprefix srcs/, \
	ft_ssl.c \
	command/command_initializer.c \
	command/command_parser.c \
	flags/flag_initializer.c \
	flags/file_reader.c \
	flags/flag_printer.c \
	utils/error_handler.c \
	utils/command_utils.c \
	hash/md5/md5.c \
	hash/sha256/sha256.c \
	)
OBJS= $(SRCS:.c=.o)

NAME= ft_ssl
FLAGS= -Wall -Werror -Wextra
INCLUDES= -Iincludes/

LFT_DIR= lib/libft
LFT_OBJS= $(wildcard $(LFT_DIR)/*.o)

all: $(NAME)

$(NAME): libft.a $(OBJS)
	@gcc $(FLAGS) $(OBJS) $(LFT_OBJS) -L$(LFT_DIR) -lft -o $(NAME)

bonus: FLAGS += -DBONUS
bonus: fclean $(NAME)

%.o: %.c
	@gcc -c $< -o $@ $(FLAGS) $(INCLUDES) -L$(LFT_DIR) -lft

libft.a:
	@make bonus -C $(LFT_DIR)

clean:
	@rm $(OBJS)
	@make -C $(LFT_DIR) clean BONUS=1

fclean: clean
	@rm $(NAME)
	@make -C $(LFT_DIR) fclean BONUS=1

re: fclean all
