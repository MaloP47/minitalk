/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:01:50 by mpeulet           #+#    #+#             */
/*   Updated: 2023/07/12 09:31:47 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
convert_and_send converts 'c' to 8 bits and sends them to 'server_pid'.
It uses SIGUSR1 and SIGUSR2 to transmit each bit.
For each bit, it checks if 'c' has the bit set using a mask (0x01 << bit).
If set, it sends SIGUSR1; otherwise, it sends SIGUSR2.
After each signal, it pauses 200 microseconds with usleep().
Repeats for all 8 bits of 'c'.
*/

void	convert_and_send(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (0x01 << bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(200);
		bit++;
	}
}

int	str_isdigit(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	i;
	int	server_pid;

	i = 0;
	server_pid = ft_atoi(av[1]);
	if (ac == 3 && str_isdigit(av[1]) && server_pid > 1)
	{
		while (av[2][i])
		{
			convert_and_send(server_pid, av[2][i]);
			i++;
		}
		convert_and_send(server_pid, 10);
	}
	else
	{
		ft_putendl_fd(C_ERROR, 1);
		ft_putendl_fd(C_ARGS, 1);
		ft_putendl_fd(C_EX_ARGS, 1);
	}
	return (0);
}
