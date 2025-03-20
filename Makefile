cc = cc

CFLAGS = -Werror -Wall -Wextra


NAME_1 = client
NAME_2 = server

CLIENT_SRCS = client.c
SERVER_SRCS = server.c



all: $(NAME_1) $(NAME_2)

$(NAME_1): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(NAME_1)

$(NAME_2): $(SERVER_SRCS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(NAME_2)

fclean:
	rm -f $(NAME_1) $(NAME_2)

re: fclean all

.Phony: clean fclean all re
