/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:48:58 by lade-lim          #+#    #+#             */
/*   Updated: 2022/10/10 21:37:48 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipex(int argc, char **argv, t_pipex *data)
{
	data->pipe_in_fd = -1;
	data->check_infile = 0;
	data->index_cmd = -1;
	data->error = 1;
	data->i = 0;
	open_infile(data, argv);
	open_outfile(data, argv, argc);
	data->cmd_nb = argc - 3;
}

void	open_infile(t_pipex *data, char **argv)
{
	data->input_file = open(argv[1], O_RDONLY);
	if (data->input_file == -1)
	{
		data->input_file = open("/dev/null", O_RDONLY);
		data->check_infile = 1;
	}
}

void	open_outfile(t_pipex *data, char **argv, int argc)
{
	data->out_file = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->out_file == -1)
		msg_error_exit(argv[argc - 1], ": Permission denied\n", 1);
	// BONUS data->out_file = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
}
