NAME = minitalk.a
NAMEB = minitalk_bonus.a

SRCS = server.c							\
	   client.c							\
	   ft_printf/ft_format.c			\
	   ft_printf/ft_printhex.c			\
	   ft_printf/ft_printf.c			\
	   ft_printf/ft_printpointer.c		\
	   ft_printf/ft_printunsigned.c		\
	   ft_printf/ft_putchar.c			\
	   ft_printf/ft_putnbr.c			\
	   ft_printf/ft_putstr.c


BONUS = server_bonus.c					\
	   client_bonus.c					\
	   ft_printf/ft_format.c			\
	   ft_printf/ft_printhex.c			\
	   ft_printf/ft_printf.c			\
	   ft_printf/ft_printpointer.c		\
	   ft_printf/ft_printunsigned.c		\
	   ft_printf/ft_putchar.c			\
	   ft_printf/ft_putnbr.c			\
	   ft_printf/ft_putstr.c


OBJS = $(SRCS:.c=.o)
OBJSB = $(BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(NAMEB)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	gcc  $(CFLAGS) minitalk.a server.c -o server
	gcc  $(CFLAGS) minitalk.a client.c -o client

$(NAMEB): $(OBJSB)
	ar -rc $(NAMEB) $(OBJSB)
	gcc  $(CFLAGS) minitalk_bonus.a server_bonus.c -o server_bonus
	gcc  $(CFLAGS) minitalk_bonus.a client_bonus.c -o client_bonus

clean:
	rm -f $(OBJS)
	rm -f $(OBJSB)

fclean: clean
	rm -f $(NAME) server client 
	rm -f $(NAMEB) client_bonus server_bonus

re: fclean all