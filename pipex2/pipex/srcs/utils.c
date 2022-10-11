/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:47:42 by lade-lim          #+#    #+#             */
/*   Updated: 2022/10/10 20:32:25 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_child(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->cmd[++i])
		free(p->cmd[i]);
	free(p->cmd);
	i = -1;
	while (++i < p->cmd_nb - 1)
		free(p->pipe_fd[i]);
	free(p->pipe_fd);
	i = -1;
	while (p->valid_cmd[++i])
		free(p->valid_cmd[i]);
	free(p->valid_cmd);
	if (p->process_id)
		free(p->process_id);
}

void	free_parent(t_pipex *p)
{
	int	i;

	i = -1;
	while (++i < p->cmd_nb - 1)
		free(p->pipe_fd[i]);
	free(p->pipe_fd);
	if (p->process_id)
		free(p->process_id);
	// free(p->path);
}

void	close_pipes(t_pipex *p)
{
	int	i;

	i = -1;
	while (++i < (p->cmd_nb - 1))
	{
		close(p->pipe_fd[i][0]);
		close(p->pipe_fd[i][1]);
	}
	close(p->input_file);
	close(p->out_file);
}
