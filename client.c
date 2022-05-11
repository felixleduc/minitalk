/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:12:25 by fleduc            #+#    #+#             */
/*   Updated: 2022/05/11 11:38:22 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

void	usage_message(void)
{
	ft_putstr_fd("usage: ./client <pid of server> <string>\n", 2);
	exit(1);
}

int	check_input(char *pid)
{
	int	i;

	i = -1;
	while (pid[++i])
		if ((pid[i] < '0') || (pid[i] > '9'))
			return (1);
	return (0);
}

char	*switch_to_bin(char *str)
{
	int		i;
	int		j;
	int		mask;
	int		c;
	char	*buffer;

	i = 0;
	j = 0;
	buffer = ft_calloc((ft_strlen(str) * 7) + 1, sizeof(char));
	while (str[i])
	{
		c = str[i];
		mask = 0x40;
		while (mask > 0)
		{
			if ((c & mask) > 0)
				buffer[j] = '1';
			else
				buffer[j] = '0';
			mask >>= 1;
			++j;
		}
		++i;
	}
	return (buffer);
}

int	main(int argc, char *argv[])
{
	int		pid_srv;
	int		i;
	char	*bin;

	if (argc != 3 || check_input(argv[1]))
		usage_message();
	pid_srv = ft_atoi(argv[1]);
	bin = switch_to_bin(argv[2]);
	i = 0;
	while (bin[i])
	{
		if (bin[i] == '0')
			kill(pid_srv, SIGUSR1);
		else if (bin[i] == '1')
			kill(pid_srv, SIGUSR2);
		++i;
		usleep(100);
	}
	free(bin);
	return (0);
}
