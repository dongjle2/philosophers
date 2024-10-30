NAME = philo

SRCS_DIR = ./srcs
OBJS_DIR = ./objs
INCL_DIR = ./includes
CFLAGS = -g -Wall -Wextra -Werror -I$(INCL_DIR)

SRCS = main \
		validate_user_input \
		validate_value_range \

SRCS := $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(SRCS)))
OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME);

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_DIR)
 
fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
