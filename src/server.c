/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:47:04 by mpeulet           #+#    #+#             */
/*   Updated: 2023/07/12 09:32:00 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
The new_handler function is a signal handler for SIGUSR1 signal.
It maintains static vars 'bit' and 'i' to track bit position and value.
When SIGUSR1 is received, it sets corresponding bit in 'i' (0x01 << bit).
Then, it increments 'bit'. If 'bit' reaches 8, it prints the character
represented by 'i' using ft_putchar_fd.
Finally, 'bit' and 'i' are reset to 0, and a SIGUSR2 signal is sent
to the process identified by siginfo->si_pid.
*/

void	new_handler(int signal, siginfo_t *siginfo, void *vd)
{
	static int	bit = 0;
	static int	i = 0;

	(void)siginfo;
	(void)vd;
	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_putchar_fd(i, 1);
		if (i == 10)
			ft_putstr_fd(S_CHEV, 1);
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_putendl_fd(S_WLC, 1);
	ft_printf(S_PID, pid);
	ft_putstr_fd(S_CHEV, 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = new_handler;
	sigemptyset(&sa.sa_mask);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
