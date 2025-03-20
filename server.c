#include <signal.h>
#include <unistd.h>

int btod(char *str)
{
	int t = 0;
	int r = 0;
	while (str[t])
	{
		r = (r * 2) + str[t] - 48;
		t++;	
	}
	return r;
}
void sighandler(int signum, siginfo_t *info, void *context)
{
	static char ptr[8];
	static int p = 0;
	static pid_t t;
	(void) context;
	if(t != info->si_pid)
		p = 0;
	t = info->si_pid;
	if(p < 8)
	{
		if (signum == SIGUSR1)
			ptr[p] = '1';
		else if (signum == SIGUSR2)
			ptr[p] = '0';
		p++;
	}
	if(p == 8)
	{
		ptr[p] = '\0';
		char c = (char)btod(ptr);
		write(1, &c, 1);
		p = 0;
	}
	if(kill(t, SIGUSR1) == -1)
		return ;
}

int main()
{
	int t = 0;
	char pp[12];
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sighandler;
	if(sigaction(SIGUSR1, &sa, NULL) == -1)
		return 0;
	if(sigaction(SIGUSR2, &sa, NULL) == -1)
		return 0;
	pid_t pid = getpid();
	while(pid > 0)
	{
		pp[t] = pid % 10 + 48;
		pid /= 10;
		t++;
	}
	while(t >= 0)
	{
		write(1, &pp[t], 1);
		t--;
	}
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
}
