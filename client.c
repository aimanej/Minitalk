#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile sig_atomic_t sigstatus = 0;

void	int_to_binary(char *str, unsigned char t)
{
	char re[12];
	int i = 0;
	int j = 0;

	while(t > 0)
	{
		re[i] = (t % 2) + 48;
		t /= 2;
		i++;

	}
	while (i <= 7)
	{
		re[i++] = '0';
	}
	while(i > 0)
	{
		str[j] = re[i - 1];
		i--;
		j++;
	}
	str[j] = '\0';
}
void sendonec(pid_t pid, char s)
{
	int i = 0;
	char s1[9];

	int_to_binary(s1, s);
	while(s1[i])
	{
		if(s1[i] == '1')
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		while(!sigstatus)
		{
		}
		sigstatus = 0;
		i++;
	}
}
void handler()
{
	sigstatus = 1;
	return;
}

int checker(char *str)
{
	int t = 0;
	while(str[t])
	{
		if(!(str[t] >= '0' && str[t] <= '9'))
			return 0;
		t++;
	}
	return 1;
}
int main(int ac, char **av)
{
	pid_t t = 0;
	int i = 0;
	int k = 0;
	
	signal(SIGUSR1, handler);
	if(ac > 1)
	{
		if(!checker(av[1]))
			return 1;
		while(av[1][i] != '\0')
		{
			t = t * 10 + (av[1][i] - '0');
			i++;
		}
		while(av[2][k])
		{
			sendonec(t, av[2][k]);
			k++;
		}
	}
	
}
