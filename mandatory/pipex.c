/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:43:49 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/26 17:09:48 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	first_child(t_data arg, int *end)
{
	int	fd;

	if (fork() == 0)
	{
		fd = open(arg.fdin, O_RDONLY, 0777);
		close(end[0]);
		if (dup2(end[1], 1) == -1 || dup2(fd, 0) == -1)
			(write(2, "\tError in first child\n", 22), exit (EXIT_FAILURE));
		close(end[1]);
		close(fd);
		execve(arg.path1, arg.cmd1, NULL);
		perror("execve");
    	exit(1);
	}
}

void	second_child(t_data arg, int *end)
{
	int	fd;

	if (fork() == 0)
	{
		fd = open(arg.fdout, O_CREAT | O_RDWR | O_TRUNC, 0644);
		close(end[1]);
		if (dup2(end[0], 0) == -1 || dup2(fd, 1) == -1)
			(write(2, "\tError in second child\n", 22), exit (EXIT_FAILURE));
		close(end[0]);
		close(fd);
		execve(arg.path2, arg.cmd2, NULL);
		write(2, "cmd not found",13);
		exit(1);

		exit(EXIT_FAILURE);
	}
}

void	pipex(t_data arg)
{
	int	end[2];

	pipe(end);
	first_child(arg, end);
	second_child(arg, end);
	close(end[0]);
	close(end[1]);
	wait(NULL);
	wait(NULL);
}

int main(int ac, char **av, char **envp)
{
	t_data	arg;
	int		x;

	if (ac == 5)
	{
		x = 1;
		arg.cmd1 = ft_parsing(&arg, av[2], envp, &x);
		x = 2;
		arg.cmd2 = ft_parsing(&arg, av[3], envp, &x);
		arg.fdin = av[1];
		arg.fdout = av[4];
		pipex(arg);
		free_all(arg);
	}
	else
		perror("less arguments");
	return (0);
}
