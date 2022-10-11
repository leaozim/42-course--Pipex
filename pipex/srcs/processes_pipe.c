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
	if (p->input_file != -1)
		close(p->input_file);
	if (p->out_file != -1)
		close(p->out_file);
	if (p->pipe_in_fd != -1)
		close(p->pipe_in_fd);
}

int	parent(t_pipex *p)
{
	int		status;
	int		i;

	i = -1;
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
			msg_error("pipex:",  "pipe creating error\n");
		pipex->process_id = fork();
		if (pipex->process_id < 0)
			msg_error_exit("fork ", ": ERROR\n", 1); //ajeitar essa saida de erro
		if (pipex->process_id == 0)
		{
			get_cmd(argv, pipex, i + 2);
			pipex->path = get_path(envp);
			check_access(pipex);
			child(pipex, i);
			execute_cmd(pipex, i);
		}
		else
		{
			if (i != 0)
				close(pipex->pipe_in_fd);
			if (i < pipex->cmd_nb - 1)
				pipex->pipe_in_fd = dup(pipex->pipe_fd[0]);
			close(pipex->pipe_fd[0]);
			close(pipex->pipe_fd[1]);
			status = parent(pipex);
			i++;
		}
	}
	return (status);
}
