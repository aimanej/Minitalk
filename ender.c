#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_binary(int t)
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
	printf("===%s", str);
		return str;

}
void sendonec(pid_t pid, char *s)
{
	int i = 0;
	int t = 0;
	char *s1;

	s1 = malloc(strlen(s)*4 + 1);
	s1[0] = '\0';
	while(s[t])
	{
		strcat(s1, int_to_binary(s[t]));
		t++;
	}
	t = 0;
	while(s1[i])
	{
		if(s1[i] == '1')
		{
			kill(pid, SIGUSR1);
			write(1,"rec1", 4);
		}
		else
		{
			kill(pid, SIGUSR2);
			write(1, "REC2", 4);
		}
		usleep(100);
		i++;
	}
	free(s1);
}
int main(int ac, char **av)
{
	pid_t t = 0;
	int i = 0;

	if(ac > 1)
	{
		while(av[1][i] != '\0')
		{
			t = t * 10 + (av[1][i] - '0');
			i++;
		}
		sendonec(t, av[2]);
	}
	
}
