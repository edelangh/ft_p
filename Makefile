# var
CC = gcc
NAME_CLIENT = client
NAME_SERVER = serveur
CFLAGS = -Wall -Wextra -Werror
OBJDIR = obj/
HEADERDIR = .

SRCS_CLIENT_DIR = client_dir/
SRCS_SERVER_DIR = server_dir/
SRCS_CLIENT2 = main.c \
			   tools.c \
			   putdir.c \
			   cd.c \
			   ftp.c \
			   ls.c
SRCS_SERVER2 = main.c \
			   tools.c \
			   cd.c \
			   ftp.c \
			   ls.c \
			   create_server.c

HEADER = ft_p.h client.h
SRCS_CLIENT = $(addprefix $(SRCS_CLIENT_DIR),$(SRCS_CLIENT2))
SRCS_SERVER = $(addprefix $(SRCS_SERVER_DIR),$(SRCS_SERVER2))
OBJS_CLIENT = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS_CLIENT)))
OBJS_SERVER = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS_SERVER)))

INCLUDES = -I libft/includes -I.

.PHONY: all clean fclean re proper libft

all: libft $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_CLIENT): libft/libft.a $(OBJS_CLIENT) $(HEADER)
	gcc $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(INCLUDES) -L libft -lft

$(NAME_SERVER): libft/libft.a $(OBJS_SERVER) $(HEADER)
	gcc $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER) $(INCLUDES) -L libft -lft


libft:
	make -C libft

$(OBJS_SERVER): | $(OBJDIR)

$(OBJS_CLIENT): | $(OBJDIR)

$(OBJDIR)%.o : %.c $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then \
		mkdir $(OBJDIR);\
		fi
	@if [ ! -d "$(OBJDIR)/$(SRCS_CLIENT_DIR)" ]; then \
		mkdir $(OBJDIR)$(SRCS_CLIENT_DIR);\
		fi
	@if [ ! -d "$(OBJDIR)/$(SRCS_SERVER_DIR)" ]; then \
		mkdir $(OBJDIR)$(SRCS_SERVER_DIR);\
		fi

clean:
	@make clean -C libft
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME_CLIENT)
	rm -rf $(NAME_SERVER)

proper: all clean

re: fclean all
