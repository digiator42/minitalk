#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int ft_atoi(char *str){
	int i = 0;
	int res = 0;
	int sign = 1;

	while(str[i] == ' ' || (str[i] >= 8 && str[i] <= 14))
		i++;
	if(str[i] == '-' || str[i] == '+')
		if(str[i++] == '-')
			sign *= -1;
	while(str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - 48);
	if (str[i])
		if (str[i] < '0' || str[i] > '9')
			return (0);	
	return res * sign;
}

static void	send_bits(int pid, char *str)
{
	int		i;
	char	bit;

	i = 8;
	while (*str)
	{
		bit = *str & 255;
		kill(pid, SIGUSR1);
		str++;
		i = 8;
		usleep(100);
	}
}

int main(int ac, char *av[]){

	int pid;

	if(ac != 3)
		return 1;
	pid = ft_atoi(av[1]);
	if(pid <= 0)
		write(STDOUT_FILENO, "\033[31mWrong pid!!\n", 17);
	else
		send_bits(pid, av[2]);
	return 0;
}