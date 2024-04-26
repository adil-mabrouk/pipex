/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:43:49 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/26 16:41:22 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

void	first_child(t_data arg, char *av, char **env, int *end)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(arg.fdin, 0) == -1 || dup2(end[1], 1) == -1)
			(write(2, "\tError in first child\n", 22), exit(EXIT_FAILURE));
		close(arg.fdin);
		close(end[0]);
		close(end[1]);
		arg.cmd = ft_parsing(&arg, av, env);
		execve(arg.path, arg.cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(NULL);
}

void	middle_child(t_data arg, char *av, char **env, int *end)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(end[0], 0) == -1 || dup2(end[1], 1) == -1)
			(write(2, "\tError in middle child\n", 22), exit(EXIT_FAILURE));
		close(end[0]);
		close(end[1]);
		arg.cmd = ft_parsing(&arg, av, env);
		execve(arg.path, arg.cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(NULL);
}

void	last_child(t_data arg, char *av, char **env, int *end)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(end[0], 0) == -1 || dup2(arg.fdout, 1) == -1)
			(write(2, "\tError in second child\n", 22), exit(EXIT_FAILURE));
		close(end[1]);
		close(end[0]);
		close(arg.fdout);
		arg.cmd = ft_parsing(&arg, av, env);
		execve(arg.path, arg.cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(NULL);
}

void	pipex(t_data arg, char **av, char **env)
{
	int	end[2];
	int	new_end[2];

	pipe(end);
	first_child(arg, av[arg.iter++], env, end);
	close(arg.fdin);
	close(end[1]);
	while (arg.iter < arg.ac - 2)
	{
		pipe(new_end);
		end[1] = new_end[1];
		middle_child(arg, av[arg.iter++], env, end);
		close(new_end[1]);
		close(end[0]);
		end[0] = new_end[0];
	}
	close(end[1]);
	last_child(arg, av[arg.iter], env, end);
	close(arg.fdout);
	close(end[0]);
	while (wait(NULL) != -1);
}
