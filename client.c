#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile sig_atomic_t sigstatus = 0;

char *int_to_binary(unsigned char t)
{
	char *str;
	char re[12];
	int i = 0;
	int j = 0;
	str = malloc(9);
	if(!str)
		return NULL;
	if(t == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return str;
	}
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
//	printf("===%s", str);
		return str;

}
void sendonec(pid_t pid, char s)
{
	int i = 0;
	char *s1;

	s1 = int_to_binary(s);
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
int main(int ac, char **av)
{
	pid_t t = 0;
	int i = 0;
	int k = 0;
	
	signal(SIGUSR1, handler);
	if(ac > 1)
	{
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
