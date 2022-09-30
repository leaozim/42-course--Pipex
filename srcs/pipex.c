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
	// ft_printf("\n[%d]CMD VALIDO = %s CMD = %s\n", i, p->valid_cmd, p->cmd[0]);
	if (i == 0)
	{
		// ft_printf("(1) pipe [%d]\n", 1);
		dup2(p->input_file, STDIN_FILENO);
		dup2(p->pipe[i][1], STDOUT_FILENO);
		// close(p->pipe[0]);
	}
	else if (i == p->cmd_nb - 1)
	// else
	{
		// ft_printf("(2) pipe [%d]\n", 2 * i - 2);
		dup2(p->pipe[i - 1][0], STDIN_FILENO);
		dup2(p->out_file, STDOUT_FILENO);
	}
	else
	{
		// ft_printf("(3) pipe [%d]\n", 2 * i - 2);
		// ft_printf("(4) pipe [%d]\n", 2 * i + 1);
		dup2(p->pipe[i - 1][0], STDIN_FILENO);
		dup2(p->pipe[i][1], STDOUT_FILENO);

		// dup2(p->pipe[2 * i - 2], STDIN_FILENO );
		// dup2(p->pipe[2 * i + 1], STDOUT_FILENO);
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
	int		pipe2 = 0;

	init_pipex(argc, argv, &pipex);
	i = -1;
	pipex.pipe = malloc(sizeof(int *) * (pipex.cmd_nb - 1));
	int k = 0;
	while (k < (pipex.cmd_nb - 1))
	{
		pipex.pipe[k] = malloc(sizeof(int) * 2);
		pipe2 = pipe(pipex.pipe[k]);
		k++;
	}
	while(pipex.cmd_nb > ++i && pipe2)
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
	int j = 0;
	while (pipex.cmd_nb > j)
	{
		ft_printf("wait %d\n", j);
		waitpid(pipex.process_id[j], &status, 0);
		j++;
	}
	close_pipes(&pipex);
	free(pipex.pipe);
	return (0);
}
