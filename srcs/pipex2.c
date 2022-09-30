/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lade-lim <lade-lim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:29:31 by lade-lim          #+#    #+#             */
/*   Updated: 2022/09/29 22:40:11 by lade-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

# define STDOUT_FILENO 1
# define STDIN_FILENO 0

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	*cmd2;
	char	**argv3;
	char	**argv2;
	int 	fd[2];
	int		pid1;
	int     status;
	int		outfile;
	int		inputfile;

	argv2 = ft_split(argv[2], ' ');
	argv3 = ft_split(argv[3], ' ');
	cmd = ft_strjoin("/usr/bin/", argv2[0]);
	cmd2 = ft_strjoin("/usr/bin/", argv3[0]);
	inputfile = open(argv[1], O_RDONLY);
	outfile =open(argv[argc - 1],  O_CREAT | O_RDWR | O_TRUNC);
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		// dup2(inputfile, STDIN_FILENO);
		// dup2(fd[1], STDOUT_FILENO);
		dup2(inputfile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);		
		close(fd[0]);
		close(inputfile);
		ft_printf("Iniciando o execv :%s\n", cmd);
		if (execve(cmd, argv2, envp) == -1)
			perror("filho não executado");
	}
	else
	{
		#define BUFFER_SIZET 1000
		char *buffer = "ola";
		int bit; 
		
		waitpid(pid1, &status, 0);
		dup2(outfile, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		bit = read(STDIN_FILENO, buffer, BUFFER_SIZET);
		ft_printf("%d\n", bit);
		while (bit > 0)
		{
			write(outfile, buffer, sizeof(buffer));
			bit = read(STDIN_FILENO, buffer, sizeof(buffer));
			ft_printf("%s\n", buffer);
			
		}
		close(fd[1]);
		close(outfile);
		// f (execve(cmd2, argv3, enivp) == -1)
		// 	perror("pai não executado");
	}
	return (0);
}
