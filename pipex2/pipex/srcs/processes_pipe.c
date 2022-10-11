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
	// printf("%d\n", p->check_infile);
	if ((p->check_infile != 1 || i != 0) && p->index_cmd != 1)
		execve(p->valid_cmd[p->index_cmd], p->cmd, NULL);
	free_child(p);
	exit(127);
}

void	child(t_pipex *p, int i)
{
	// printf("infile %d\n", p->input_file);
	// if (i == 0)
	// {
	// 	dup2(p->input_file, STDIN_FILENO);
	// 	dup2(p->pipe_fd[i][1], input_file);
	// }
	// else if (i == p->cmd_nb - 1)
	// {
	// 	dup2(p->pipe_fd[i - 1][0], STDIN_FILENO);
	// 	dup2(p->out_file, STDOUT_FILENO);
	// }
	// else
	// {
	// 	dup2(p->pipe_fd[i - 1][0], STDIN_FILENO);
	// 	dup2(p->pipe_fd[i][1], STDOUT_FILENO);
	// }
	if (i == 0)
	{
		dup2(p->input_file, STDIN_FILENO);
		dup2(p->pipe_fd[1], STDOUT_FILENO);
	}
	else if (i == p->cmd_nb - 1)
	{
		dup2(p->input_file, STDIN_FILENO);
		dup2(p->out_file, STDOUT_FILENO);
	}
	else
	{
		dup2(p->pipe_in_fd, STDIN_FILENO);
		dup2(p->pipe_fd[0], STDOUT_FILENO);
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
		waitpid(p->process_id[i], &status, 0);
	return (WEXITSTATUS(status));
}

int	start_pipex(char **argv, char **envp, t_pipex *pipex)
{
	int		i;
	// int		exit_code;
	// int		status;

	// printf("%d\n", pipex->check_infile);

	i = -1;
	while (pipex->cmd_nb > ++i)
	{
		pipex->process_id[i] = fork();
		if (pipex->process_id[i] < 0)
			msg_error_exit("fork ", ": ERROR\n", 1); //ajeitar essa saida de erro
		if (pipex->process_id[i] == 0)
		{
			get_cmd(argv, pipex, i + 2);
			pipex->path = get_path(envp);
			check_access(pipex);
			child(pipex, i);
			close_pipes(pipex);
			execute_cmd(pipex, i);
		}
		// else
		// {
		// 	close_pipes(pipex);
		// 	cd(pipex->process_id[i], &status, 0);
		// 	// free_parent(pipex);
		// }
		else
		{
			if (i != 0)
				close(pipex->pipe_in_fd);
			if (i < pipex->cmd_nb - 1)
				pipex->pipe_fd = dup(pipex->pipe_fd[0]);
			if (pipex->input_file != -1)
				close(pipex->input_file);
			if (pipex->out_file != -1)
				close(pipex->out_file);
			if (pipex->pipe_in_fd != -1)
				close(pipex->pipe_in_fd);
			i++;
		}
	}
	// close_pipes(pipex);
	// exit_code = parent(pipex);
	// free_parent(pipex);
	return (0);
}
