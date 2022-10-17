/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:47:42 by lade-lim          #+#    #+#             */
/*   Updated: 2022/10/12 20:27:22 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_child(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->cmd[++i])
		free(p->cmd[i]);
	free(p->cmd);
	i = -1;
	while (p->valid_cmd[++i])
		free(p->valid_cmd[i]);
	free(p->valid_cmd);
}

void	close_files_fd(t_pipex *p)
{
	if (p->input_file != -1)
		close(p->input_file);
	if (p->out_file != -1)
		close(p->out_file);
	if (p->pipe_in_fd != -1)
		close(p->pipe_in_fd);
}

void	close_pipes_fd(t_pipex *p)
{
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
}
