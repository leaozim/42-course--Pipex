/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checking_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:04:54 by lade-lim          #+#    #+#             */
/*   Updated: 2022/10/12 20:27:00 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	replace_char(char **str, int original_value, int value_substituted)
{
	size_t		i;
	int			quotes;
	char		*str_aux;

	i = -1;
	str_aux = *str;
	quotes = 0;
	while (str_aux[++i])
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

	replace_char(&str[index], SPACE, TEMP_VALUE);
	p->cmd = ft_split(str[index], TEMP_VALUE);
		i = -1;
	while (p->cmd[++i])
	{
		replace_char(&p->cmd[i], TEMP_VALUE, SPACE);
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
	int		index;
	char	*temp;

	index = -1;
	while (p->path[++index])
		;
	p->valid_cmd = malloc((sizeof(char *) * (index + 1)));
	p->valid_cmd[index] = NULL;
	index = -1;
	while (p->path[++index])
	{
		temp = ft_strjoin(p->path[index], "/");
		free(p->path[index]);
		p->valid_cmd[index] = ft_strjoin(temp, *p->cmd);
		free (temp);
		if (!access(p->valid_cmd[index], F_OK | X_OK))
		{
			p->index_cmd = index;
			p->check_cmd = VAL_CMD;
		}
	}
	if (p->check_cmd != VAL_CMD && (p->check_infile != INV_INFILE || p->i != 0))
		msg_error(*p->cmd, ": command not found\n");
	free(p->path);
}
