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

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	gcc  $(CFLAGS) minitalk.a server.c -o server
	gcc  $(CFLAGS) minitalk.a client.c -o client

clean:
	rm -f $(OBJS)
	rm -f $(OBJSB)

fclean: clean
	rm -f $(NAME) server client 

re: fclean all