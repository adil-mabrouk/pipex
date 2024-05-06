/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:16:26 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/06 18:13:18 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

int	ft_open(char *title, int info)
{
	int	file;

	if (info == 0)
		file = open(title, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (info == 1)
		file = open(title, O_RDONLY, 0777);
	if (info == 2)
		file = open(title, O_CREAT | O_RDWR | O_TRUNC, 0777);
	return (file);
}

void	here_doc(t_data *arg, char **av)
{
	char	*line;
	int		end[2];

	if (pipe(end) == -1)
		perror("pipe error...");
	while (1)
	{
		write(1, "heredoc>", 8);
		line = get_next_line(0);
		if (!line || ft_strcmp_nl(av[2], line) == 0)
			break ;
		write(end[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(end[1]);
	arg->fdin = end[0];
	(*arg).iter = 3;
}

int	main(int ac, char **av, char **envp)
{
	t_data	arg;

	arg = (t_data){0};
	if (ac >= 5)
	{
		if (ac > 5 && ft_strcmp(av[1], "here_doc") == 0)
		{
			arg.fdout = ft_open(av[ac - 1], 0);
			arg.outfile = av[ac - 1];
			here_doc(&arg, av);
		}
		else
		{
			arg.fdin = ft_open(av[1], 1);
			arg.fdout = ft_open(av[ac - 1], 2);
			arg.infile = av[1];
			arg.outfile = av[ac - 1];
			arg.iter = 2;
		}
		arg.ac = ac;
		pipex(arg, av, envp);
	}
	else
		write(2, "wrong number of arguments\n", 26);
	return (0);
}
