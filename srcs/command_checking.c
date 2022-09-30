/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:04:54 by lade-lim          #+#    #+#             */
/*   Updated: 2022/09/29 23:14:33 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_path(char **envp)
{
	int		i;
	// char	*temp;
	char	**array_envp = NULL;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			array_envp = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	return (array_envp);
}

void	get_cmd(char *argv, t_pipex *p)
{
	p->cmd = ft_split(argv, ' ');
}

int	check_access(t_pipex *p)
{
	int		i;
	char	*temp;

	i = 0;
	while (p->path[i])
	{
		// ft_printf("%d\n", i);
		temp = ft_strjoin(p->path[i], "/");
		p->valid_cmd = ft_strjoin(temp, *p->cmd);
		free (temp);
		if (access(p->valid_cmd, F_OK | X_OK) == 0)
		{
			// ft_printf("ok  dentro = %s\n", p->valid_cmd);
			return (0);
		}
		i++;
	}
	return (1);
}
