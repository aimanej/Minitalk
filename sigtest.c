#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
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
	}/*
	if (signum == SIGUSR1)
		write(1, "1", 1);
	if (signum == SIGUSR2)
		write(1, "0", 1);
		*/
}

void sig2()
{
	write(1, "0", 1);
}

int main()
{
	int t = 0;
	char pp[12];
	struct sigaction sa = {0};

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sighandler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
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
	write(1, "--->", 4);

	while (1)
	{
		pause();
	}
}
