NAME = philo

SRCS_DIR = ./srcs
OBJS_DIR = ./objs
INCL_DIR = ./includes
CFLAGS = -g -Wall -Wextra -Werror -I$(INCL_DIR)

SRCS = main \
		validate_user_input \
		validate_value_range \
		philo_state \
		sleep \
		utils_eat \
		utils_mutex \
		resources \
		pre_setup_thread_create \
		thread_routines \
		manage_thread \
		mutex_collection \
		libft \
		utils_setup \
		utils2_mutex \

SRCS := $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(SRCS)))
# OBJS = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

$(info OBJS: $(OBJS))

all: $(OBJS_DIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
 
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re