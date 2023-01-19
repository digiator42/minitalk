/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:03:02 by ahassan           #+#    #+#             */
/*   Updated: 2023/01/19 14:36:36 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - 48);
	if (str[i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (res * sign);
}

void	ft_handler(int signum)
{
	if (signum == SIGUSR2)
	{
		write(STDOUT_FILENO, "\033[32mSent full msg \n", 22);
		write(STDOUT_FILENO, "\033[33mrecieved signal back from server\n", 38);
		exit(0);
	}
}

static void	send_null(int pid)
{
	int		i;
	char	bit;

	i = 8;
	while (i--)
	{
		bit = ('\0' >> i) & 1;
		if (bit == 1){
			kill(pid, SIGUSR1);
		}
		else{
			kill(pid, SIGUSR2);
		}
		usleep(100);
	}
}

static void	send_bits(int pid, char *str)
{
	int		i;
	char	bit;

	i = 8;
	while (*str)
	{
		while (i--)
		{
			bit = (*str >> i) & 1;
		if (bit == 1){
			write(1, "1", 1);
			kill(pid, SIGUSR1);
		}
		else{
			write(1, "0", 1);
			kill(pid, SIGUSR2);
		}
			usleep(150);
		}
		str++;
		i = 8;
		usleep(150);
	}
}

int	main(int ac, char *av[])
{
	int	pid;

	signal(SIGUSR2, &ft_handler);
	signal(SIGUSR1, &ft_handler);
	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		write(STDOUT_FILENO, "\033[31mWrong pid!!\n", 17);
	else
	{
		send_bits(pid, av[2]);
		send_null(pid);
	}
	return (0);
}
