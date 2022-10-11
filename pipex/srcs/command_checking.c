/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:04:54 by lade-lim          #+#    #+#             */
/*   Updated: 2022/10/10 21:10:13 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_cmd_2(char **str, int original_value, int value_substituted)
{
	size_t		i;
	int		quotes;
	char	*str_aux;

	i = -1;
	str_aux =  *str;
	quotes = 0;
	while(str_aux[++i])
	{
		if (str_aux[i] == SINGLE_QUOTES)
			quotes = !quotes;
		else if (str_aux[i] == original_value && !quotes)
			str_aux[i] = value_substituted;
	}
}

void	get_cmd(char **str, t_pipex *p, int index)
{
	int		i;
	char	*aux;

	get_cmd_2(&str[index], SPACE, TEMP_VALUE);
	p->cmd = ft_split(str[index], TEMP_VALUE);
		i = -1;
	while (p->cmd[++i])
	{
		get_cmd_2(&p->cmd[i], TEMP_VALUE, SPACE);
		aux = p->cmd[i];
		p->cmd[i] = ft_strtrim(p->cmd[i], "'");
		free(aux);
	}
}

char	**get_path(char **envp)
{
	int		i;
	char	**array_envp;

	i = -1;
	array_envp = NULL;
	while (++i, *envp && envp[i][0] != '\0')
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			array_envp = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	return (array_envp);
}

void	check_access(t_pipex *p)
{
	int		i;
	char	*temp;
	int		erro;

	i = -1;
	erro = 1;
	while (p->path[++i])
		;
	p->valid_cmd = malloc((sizeof(char *) * (i + 1)));
	p->valid_cmd[i] = NULL;
	i = -1;
	while (p->path[++i])
	{
		temp = ft_strjoin(p->path[i], "/");
		free(p->path[i]);
		p->valid_cmd[i] = ft_strjoin(temp, *p->cmd);
		free (temp);
		if (!access(p->valid_cmd[i], F_OK | X_OK))
		{
			p->index_cmd = i;
			p->error = 0;
		}
	}
	if (p->error != 0)
		msg_error(*p->cmd, ": command not found\n");
	free(p->path);
}
