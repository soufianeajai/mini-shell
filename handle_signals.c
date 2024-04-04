/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:56:14 by sajaite           #+#    #+#             */
/*   Updated: 2024/04/04 21:56:16 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtin.h"
#include "execution/execute.h"
#include "minishell.h"

void	disable_raw_mode(void)
{
	struct termios	new_termios;
	struct termios	orig_termios;

	tcgetattr(0, &orig_termios);
	new_termios = orig_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exitcode = 1;
	}
	if (signal == SIGQUIT)
		rl_redisplay();
}

void	handle_signals(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putstr_fd("Error: signal\n", 2);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		ft_putstr_fd("Error: signal\n", 2);
}
