/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:47:42 by lade-lim          #+#    #+#             */
/*   Updated: 2022/09/29 23:32:53 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipex *p)
{
	int i;

	i = 0;
	while(i < (p->cmd_nb - 1))
	{
		close(p->pipe[i][0]);
		close(p->pipe[i][1]);
		i++;
	}
	close(p->input_file);
	close(p->out_file);
}

void	child(t_pipex *p, int i, char **envp)
{
	if (i == 0)
	{
		dup2(p->input_file, STDIN_FILENO);
		dup2(p->pipe[i][1], STDOUT_FILENO);
	}
	else if (i == p->cmd_nb - 1)
	{
		dup2(p->pipe[i - 1][0], STDIN_FILENO);
		dup2(p->out_file, STDOUT_FILENO);
	}
	else
	{
		dup2(p->pipe[i - 1][0], STDIN_FILENO);
		dup2(p->pipe[i][1], STDOUT_FILENO);
	}
	close_pipes(p);	
	if (execve( p->valid_cmd, p->cmd, envp) == -1)
		perror("filho não executado");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		status;

	init_pipex(argc, argv, &pipex);
	i = -1;
	pipex.pipe = malloc(sizeof(int *) * (pipex.cmd_nb - 1));
	int k = 0;
	while (k < (pipex.cmd_nb - 1))
	{
		pipex.pipe[k] = malloc(sizeof(int) * 2);
		pipe(pipex.pipe[k]);
		k++;
	}
	while(pipex.cmd_nb > ++i)
	{
		get_cmd(argv[i + 2], &pipex);
		pipex.path = get_path(envp);
		if (check_access(&pipex))
		{
			ft_printf("deu ruim\n");
		}
		pipex.process_id[i] = fork();
		if (pipex.process_id[i] == 0)
		{
			ft_printf("proccess %d\n", i);
			child(&pipex, i, envp);
		}
	}
	close_pipes(&pipex);
	int j = 0;
	while (pipex.cmd_nb > j)
	{
		waitpid(-1, &status, 0);
		j++;
	}
	free(pipex.pipe);
	return (0);
}
