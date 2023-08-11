/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:38:05 by mpeulet           #+#    #+#             */
/*   Updated: 2023/07/12 09:37:33 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include "libft.h"
# include "messages.h"

typedef struct s_mini
{
	char	*s;
	int		waiting;
}		t_minitalk;

/* *** client.c & bonus *** */

void	convert_and_send(int server_pid, char c);
int		str_isdigit(char *s);

/* *** server.c & bonus *** */

void	new_handler(int signal, siginfo_t *siginfo, void *vd);

#endif