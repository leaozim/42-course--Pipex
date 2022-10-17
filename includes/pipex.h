/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:33:36 by lade-lim          #+#    #+#             */
/*   Updated: 2022/10/17 12:34:56 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../my_libs/ft_libft/libft.h"	
# include "../my_libs/ft_printf/ft_printf.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

# define STDOUT_FILE 1
# define STDIN_FILE 0
# define SINGLE_QUOTES 39 
# define TEMP_VALUE -1
# define SPACE 32
# define DOUBLE_QUOTES 34
# define INV_INFILE 1
# define VAL_INFILE 0
# define FIRST_CMD 0
# define INV_CMD 1
# define VAL_CMD 0

typedef struct s_pipex
{
	char	**path;
	char	**cmd;
	char	**valid_cmd;
	char	**array_envp;
	int		check_infile;
	int		check_cmd;
	int		input_file;
	int		out_file;
	int		process;
	int		cmd_nb;
	int		last_cmd;
	int		process_id;
	int		pipe_fd[2];
	int		pipe_in_fd;
	int		index_cmd;
	int		exit_code;
	int		*child;
	int		i;
}	t_pipex;

void	check_arguments(int argc, char **argv);
void	init_pipex(int argc, char **argv, t_pipex *data);
void	init_pipes(t_pipex *data);
void	open_infile(t_pipex *data, char **argv);
void	open_outfile(t_pipex *data, char **argv, int argc);
void	start_pipex(char **argv, char **envp, t_pipex *pipex);
void	get_cmd(char **argv, t_pipex *p, int index);
void	replace_char(char **str, int original_value, int value_substituted);
char	**get_path(char **envp);
void	check_access(t_pipex *p);
void	child(t_pipex *p);
void	parent(t_pipex *p);
void	msg_error(char *str1, char *str2);
void	msg_error_exit(char *str1, char *str2, int exit_code);
void	free_child(t_pipex *p);
void	close_pipes_fd(t_pipex *p);
void	close_files_fd(t_pipex *p);
void	execute_cmd(t_pipex *p);

#endif
