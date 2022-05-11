/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:04:04 by fleduc            #+#    #+#             */
/*   Updated: 2022/05/11 14:04:25 by fleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

char	g_bin[7];

void	ft_putchar(void)
{
	int	bin;
	int	total;
	int	i;

	bin = 64;
	total = 0;
	i = 0;
	while (g_bin[i])
	{
		if (g_bin[i] == '1')
			total += bin;
		bin /= 2;
		++i;
	}
	write(1, &total, 1);
}

void	signal_handler(int signum)
{
	static int	i;
	int			j;

	if (!i)
		i = 0;
	if (signum == SIGUSR1)
		g_bin[i] = '0';
	else if (signum == SIGUSR2)
		g_bin[i] = '1';
	++i;
	if (ft_strlen(g_bin) == 7)
	{
		ft_putchar();
		j = -1;
		while (g_bin[++j])
			g_bin[j] = '\0';
		i = 0;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd("The pid is: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	while (1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
	}
	return (0);
}
