/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:43:49 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/06 16:22:51 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	first_child(t_data arg, char *av, int *end, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		if (dup2(end[1], 1) == -1 || dup2(arg.fdin, 0) == -1)
		{
			write(2, arg.infile, ft_strlen(arg.infile));
			write(2, ": No such file or directory\n", 28);
			exit (EXIT_FAILURE);
		}
		close(end[1]);
		close(arg.fdin);
		arg.cmd = ft_parsing(&arg, av, env);
		execve(arg.path, arg.cmd, NULL);
		write(2, arg.cmd[0], ft_strlen(arg.cmd[0]));
		write(2, ": command not found\n", 20);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(NULL);
}

void	second_child(t_data arg, char *av, int *end, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(end[1]);
		if (dup2(end[0], 0) == -1 || dup2(arg.fdout, 1) == -1)
		{
			write(2, arg.outfile, ft_strlen(arg.outfile));
			write(2, ": No such file or directory\n", 28);
			exit (EXIT_FAILURE);
		}
		close(end[0]);
		close(arg.fdout);
		arg.cmd = ft_parsing(&arg, av, env);
		execve(arg.path, arg.cmd, NULL);
		write(2, arg.cmd[0], ft_strlen(arg.cmd[0]));
		write(2, ": command not found\n", 20);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(NULL);
}

void	pipex(t_data arg, char **av, char **env)
{
	int	end[2];

	if (pipe(end) == -1)
		perror("pipe error...");
	first_child(arg, av[2], end, env);
	close(arg.fdin);
	second_child(arg, av[3], end, env);
	close(arg.fdout);
	close(end[0]);
	close(end[1]);
	while (wait(NULL) != -1)
		;
}

int	main(int ac, char **av, char **envp)
{
	t_data	arg;

	if (ac == 5)
	{
		arg.infile = av[1];
		arg.fdin = open(av[1], O_RDONLY, 0777);
		arg.outfile = av[4];
		arg.fdout = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
		pipex(arg, av, envp);
		free(arg.path);
	}
	else
		write(2, "wrong number of arguments\n", 26);
	return (0);
}
