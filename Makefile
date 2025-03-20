cc = cc

CFLAGS = -Wall -Wextra -Werror


NAME_1 = client
NAME_2 = server
NAME_3 = client_bonus
NAME_4 = server_bonus

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

CLIENT_BONUS_SRCS = client_bonus.c
SERVER_BONUS_SRCS = server_bonus.c



all: $(NAME_1) $(NAME_2)

bonus: $(NAME_3) $(NAME_4)

$(NAME_1): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(NAME_1)

$(NAME_2): $(SERVER_SRCS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(NAME_2)

$(NAME_3): $(CLIENT_BONUS_SRCS)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_SRCS)

$(NAME_4): $(SERVER_BONUS_SRCS)
        $(CC) $(CFLAGS) $(SERVER_BONUS_SRCS)

fclean:
	rm -f $(NAME_1) $(NAME_2)

re: fclean all

.Phony: clean fclean all re
