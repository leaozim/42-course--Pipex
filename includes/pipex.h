/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:33:36 by lade-lim          #+#    #+#             */
/*   Updated: 2022/09/29 23:08:42 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../my_libs/ft_libft/libft.h"	
# include "../my_libs/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define STDOUT_FILENO 1
# define STDIN_FILENO 0

typedef struct s_pipex
{
	int		input_file;
	int		out_file;
	int		process;
	int		cmd_nb;
	char	**path;
	char	**cmd;
	char	*valid_cmd;
	int		*process_id;
	int		*child;
	int		**pipe;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
void	init_pipex(int argc, char **argv, t_pipex *data);
void	get_cmd(char *argv, t_pipex *p);
char	**get_path(char **envp);
int		check_access(t_pipex *p);

#endif