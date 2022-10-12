/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:29:00 by de-lim            #+#    #+#             */
/*   Updated: 2022/10/10 21:37:09 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_arguments(int argc, char **argv)
{	
	if (argc != 5)
		msg_error_exit("syntax error", "\n", 1);
	if (access(argv[1], F_OK))
		msg_error(argv[1], ": No such file or directory\n");
}

void	msg_error_exit(char *str1, char *str2, int exit_code)
{
	msg_error(str1, str2);
	exit(exit_code);
}

void	msg_error(char *str1, char *str2)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}
