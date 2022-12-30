NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lpthread
TEST_FLAGS = -g -fsanitize=thread

SRCS = main.c \
	   is_atoi.c \
	   ft_isspace.c ft_isdigit.c ft_atoi.c \
	   is_validation_args.c \
	   set_info.c \
	   get_time_ms.c \
	   philosopher.c


INCLUDES_DIR = ./includes
SRCS_DIR = ./srcs
OBJS_DIR = ./objs

INCLUDE = $(addprefix -I, $(INCLUDES_DIR))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

.PHONY: all clean fclean bonus re test_overflow

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS)

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
	norminette ./srcs/ ./includes | grep 'Error'

test_overflow: $(OBJS)
	$(CC) -g -fsanitize=address -o $@ $^

test_thread: $(OBJS)
	$(CC) $(TEST_FLAGS) -o $@ $^
