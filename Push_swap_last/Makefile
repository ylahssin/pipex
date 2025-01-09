NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb

SRCDIR = src
BONUSDIR = src_bonus
LIBFTDIR = Libft
MANDATORY_SRCS = $(SRCDIR)/main.c\
                 #$(SRCDIR)/execution.c \
                 #$(SRCDIR)/execution2.c \
                 #$(SRCDIR)/parsing.c \
                 #$(SRCDIR)/ft_perror.c \
                 #$(SRCDIR)/fun_helper.c

BONUS_SRCS = $(BONUSDIR)/pipex_bonus.c \
             $(BONUSDIR)/execution_bonus.c \
             $(BONUSDIR)/execution2_bonus.c \
             $(BONUSDIR)/parsing_bonus.c \
             $(BONUSDIR)/ft_perror_bonus.c \
             $(BONUSDIR)/fun_helper_bonus.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT = $(LIBFTDIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BONUSDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

