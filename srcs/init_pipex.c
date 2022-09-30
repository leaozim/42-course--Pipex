/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:48:58 by lade-lim          #+#    #+#             */
/*   Updated: 2022/09/29 15:32:20 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipex(int argc, char **argv, t_pipex *data)
{
	data->input_file = open(argv[1], O_RDONLY);
	data->out_file = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	data->cmd_nb = argc - 3;
}
