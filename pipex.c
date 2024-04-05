/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:43:49 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/05 00:07:23 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(char *path, int *end, char **av)
{
	int	fd;
	char	**cmds;
	if (fork() == 0)
	{
		fd = open("pipex.h", O_RDONLY, 0777);
		close(end[0]);
		if (dup2(end[1], 1) == -1 || dup2(fd, 0) == -1)
			(write(2, "Error\n", 6), exit (EXIT_FAILURE));
		close(end[1]);
		close(fd);
		cmds = ft_split(av[2], ' ');
		execve(path, cmds, NULL);
		exit(EXIT_FAILURE);
	}
}

void	second_child(char *path, int *end, char **av)
{
	(void)path;
	(void)av;
	int	fd;
	char	**cmds;
	
	if (fork() == 0)
	{
		fd = open("file", O_CREAT | O_RDWR | O_TRUNC, 0777);
		close(end[1]);
		if (dup2(end[0], 0) == -1 || dup2(fd, 1) == -1)
			(write(2, "Error\n", 6), exit (EXIT_FAILURE));
		close(end[0]);
		close(fd);
		cmds = ft_split(av[3], ' ');
		//printf("%s %s %s\n", path, cmds[0], cmds[1]);
		execve(path, cmds, NULL);
		exit(EXIT_FAILURE);
	}
}

void	pipex(char **av, char *path1, char *path2)
{
	int	end[2];

	pipe(end);
	first_child(path1, end, av);
	second_child(path2, end, av);
	close(end[0]);
	close(end[1]);
	wait(NULL);
	wait(NULL);
}

int main(int ac, char **av, char **envp)
{
	t_args	arg;

	if (ac == 5)
	{
		arg.cmd1 = ft_parsing(arg, av[2], envp);
		arg.cmd2 = ft_parsing(arg, av[3], envp);
		pipex(arg, av);
		free(arg.cmd1);
		free(arg.cmd2);
		
	}
	return (0);
}
