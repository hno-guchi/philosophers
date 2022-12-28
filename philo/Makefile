NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	   is_atoi.c ft_atoi.c \
	   initialize_time.c is_collect_value.c

INCLUDES_DIR = ./includes
SRCS_DIR = ./srcs
OBJS_DIR = ./objs

INCLUDE = $(addprefix -I, $(INCLUDES_DIR))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

.PHONY: all clean fclean bonus re test_overflow

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

bonus: all

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	norminette -v
	norminette ./libft ./srcs/ ./includes | grep 'Error'

test_overflow: $(OBJS)
	$(CC) -g -fsanitize=address -o $(NAME) $^ -L$(LIBFT_DIR) $(LIBFT_LIB)
