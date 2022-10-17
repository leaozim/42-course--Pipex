/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_pipe_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:29:00 by de-lim            #+#    #+#             */
/*   Updated: 2022/10/12 20:27:18 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	execute_cmd(t_pipex *p)
{
	if ((p->check_infile != INV_INFILE || p->i != FIRST_CMD)
		&& p->index_cmd != 1 && p->check_cmd != INV_CMD)
		execve(p->valid_cmd[p->index_cmd], p->cmd, NULL);
	free_child(p);
	exit(127);
}

void	parent(t_pipex *p)
{
	int		status;
	int		index;

	if (p->i != 0)
		close(p->pipe_in_fd);
	if (p->i < p->cmd_nb - 1)
		p->pipe_in_fd = dup(p->pipe_fd[0]);
	close_pipes_fd(p);
	index = -1;
	while (p->cmd_nb > ++index)
		waitpid(p->process_id, &status, 0);
	p->exit_code = WEXITSTATUS(status);
}

void	child(t_pipex *p)
{
	if (p->i == FIRST_CMD)
	{
		dup2(p->input_file, STDIN_FILENO);
		dup2(p->pipe_fd[1], STDOUT_FILENO);
	}
	else if (p->i == p->last_cmd)
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

void	start_pipex(char **argv, char **envp, t_pipex *pipex)
{
	while (pipex->cmd_nb > pipex->i)
	{
		if (pipe(pipex->pipe_fd) == -1)
			msg_error("pipe: ", "creating error\n");
		pipex->process_id = fork();
		if (pipex->process_id < 0)
			msg_error_exit("fork: ", "creating error\n", 1);
		if (pipex->process_id == 0)
		{
			get_cmd(argv, pipex, pipex->i + 2);
			pipex->path = get_path(envp);
			check_access(pipex);
			child(pipex);
			close_files_fd(pipex);
			execute_cmd(pipex);
		}
		else
			parent(pipex);
		pipex->i++;
	}
}
