/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:43:46 by mpeulet           #+#    #+#             */
/*   Updated: 2023/07/12 09:32:08 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_minitalk	g_mini = {NULL, 1};

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
		while (g_mini.waiting)
			;
		g_mini.waiting = 1;
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

/*
The signal_handler function handles the SIGUSR2 signal.
It maintains the static variable to track the number of characters sent.
When the signal is SIGUSR2, it increments 'char_sent' and checks if it equals
the length of the string. If 'char_sent' is equal to the length of 'g_str',
it prints a notification.
*/

void	signal_handler(int signal)
{
	static size_t	char_sent = 0;	

	g_mini.waiting = 0;
	if (signal == SIGUSR2)
	{
		char_sent++;
		if (char_sent == ft_strlen(g_mini.s))
		{
			ft_putstr_fd(NOTIFICATION_R1, 1);
			ft_putendl_fd(NOTIFICATION_R2, 1);
			ft_printf("\nYour message was : [%s]\n", g_mini.s);
			ft_putstr_fd(UNICODE, 1);
		}
	}
}

/*
The def_sigaction sets up signal actions for SIGUSR1 and SIGUSR2 signals.
It assigns the signal_handler function as the signal handler.
The SA_RESTART flag is set to ensure interrupted system calls
are automatically restarted. If the sigaction function fails
for SIGUSR1 or SIGUSR2, error messages are displayed.
*/

void	def_sigaction(void)
{
	struct sigaction	sa_action;

	sa_action.sa_handler = &signal_handler;
	sa_action.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa_action, NULL) == -1)
		ft_putendl_fd(SA_USR1_FAIL, 1);
	if (sigaction(SIGUSR2, &sa_action, NULL) == -1)
		ft_putendl_fd(SA_USR2_FAIL, 1);
}

int	main(int ac, char **av)
{
	int	i;
	int	server_pid;

	g_mini.s = av[2];
	i = 0;
	server_pid = ft_atoi(av[1]);
	if (ac == 3 && str_isdigit(av[1]) && server_pid > 1)
	{
		ft_putendl_fd(C_NOTIFICATION, 1);
		def_sigaction();
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
