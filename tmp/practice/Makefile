CC = cc
CFLAGS = -Wall -Wextra -Werror
THREAD_FLAG = -fsanitize=thread

create:
	$(CC) $(CFLAGS) create.c

join:
	$(CC) $(CFLAGS) join.c

data_race_create:
	$(CC) $(THREAD_FLAG) create.c

data_race_join:
	$(CC) $(THREAD_FLAG) join.c
