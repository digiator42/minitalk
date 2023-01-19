/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:03:04 by ahassan           #+#    #+#             */
/*   Updated: 2023/01/12 22:53:24 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_handler(int signum, siginfo_t *info, void *context)
{
	static int				len;
	static unsigned char	character;

	(void)context;
	if (signum == SIGUSR1)
		character = character << 1 | 1;
	else
		character = character << 1 | 0;
	len++;
	if (len == 8)
	{
		if (character == '\0')
			kill(info->si_pid, SIGUSR2);
		else
			kill(info->si_pid, SIGUSR1);
		write(1, &character, 1);
		character = 0;
		len = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;
	struct sigaction	sa2;

	pid = getpid();
	ft_printf("%d\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sa2.sa_flags = SA_SIGINFO;
	sa2.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	while (1)
		pause();
}
