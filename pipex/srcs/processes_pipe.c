/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:29:00 by de-lim            #+#    #+#             */
/*   Updated: 2022/10/10 22:14:11 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd(t_pipex *p, int i)
{
	if ((p->check_infile != 1 || i != 0) && p->index_cmd != 1 && p->error != 1)
		execve(p->valid_cmd[p->index_cmd], p->cmd, NULL);
	free_child(p);
	exit(127);
}

void	child(t_pipex *p, int i)
{
	if (i == 0)
	{
		dup2(p->input_file, STDIN_FILENO);
		dup2(p->pipe_fd[1], STDOUT_FILENO);
	}
	else if (i == p->cmd_nb - 1)
	{
		dup2(p->pipe_in_fd, STDIN_FILENO);
		dup2(p->out_file, STDOUT_FILENO);
	}
	else
	{
		dup2(p->pipe_in_fd, STDIN_FILENO);
		dup2(p->pipe_fd[1], STDOUT_FILENO);
	}
}

int	parent(t_pipex *p)
{
	int		status;
	int		i;

	i = -1;
	if (i != 0)
		close(p->pipe_in_fd);
	if (i < p->cmd_nb - 1)
		p->pipe_in_fd = dup(p->pipe_fd[0]);
	close_pipes_fd(p);
	while (p->cmd_nb > ++i)
		waitpid(p->process_id, &status, 0);
	return (WEXITSTATUS(status));
}

int	start_pipex(char **argv, char **envp, t_pipex *pipex)
{
	int		i;
	int		status;

	i = 0;
	while (pipex->cmd_nb > i)
	{
		if (pipe(pipex->pipe_fd) == -1)
			msg_error("pipe: ",  "creating error\n");
		pipex->process_id = fork();
		if (pipex->process_id < 0)
			msg_error_exit("fork: ", "creating error\n", 1);
		if (pipex->process_id == 0)
		{
			get_cmd(argv, pipex, i + 2);
			pipex->path = get_path(envp);
			check_access(pipex, i);
			child(pipex, i);
			close_files_fd(pipex);
			execute_cmd(pipex, i);
		}
		else
		{
			status = parent(pipex);
			i++;
		}
	}
	return (status);
}
