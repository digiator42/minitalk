#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void	ft_handler(int signum)
{
	if(signum == SIGUSR1)
		write(1, "got process SIGUSR1\n", 21);
	else	
		write(1, "got process id, SIGUSR2\n", 25);
}		
int main(){
	int pid = getpid();
	printf("%d\n", pid);

	struct sigaction sa;
	sa.sa_handler = &ft_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	
	struct sigaction sa2;
	sa2.sa_handler = &ft_handler;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = SA_RESTART;


	sigaction(SIGUSR1, &sa, NULL);	
	sigaction(SIGUSR2, &sa2, NULL);	
	while (1)
		pause();
}
