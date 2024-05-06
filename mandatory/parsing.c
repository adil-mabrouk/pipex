/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:04:39 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/06 16:16:52 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	ft_strlen_of_2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	while (s2 && *s2)
	{
		s2++;
		i++;
	}
	return (i);
}

int	is_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (i == ft_strlen_of_2(s, NULL))
		return (1);
	return (0);
}

char	*ft_strstr(char **env, char *find)
{
	int	i;
	int	k;

	i = 0;
	while (env[i])
	{
		k = 0;
		while (find[k] && env[i][k] && env[i][k] == find[k])
			k++;
		if (!find[k])
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	**find_path(t_data *arg, char **path, char **cmd)
{
	char	*joined;
	int		i;

	joined = NULL;
	i = 0;
	while (path[i])
	{
		joined = ft_strjoin(path[i], cmd[0]);
		if (joined && access(joined, F_OK) == 0)
		{
			(*arg).path = ft_strdup(joined);
			return (ft_free(path), cmd);
		}
		i++;
	}
	return (ft_free(path), cmd);
}

char	**ft_parsing(t_data *arg, char *av, char **env)
{
	char	*s;
	char	**cmd;
	char	**path;

	if ((av && !av[0]) || is_whitespace(av))
	{
		write(2, av, ft_strlen(av));
		write(2, ": command not found\n", 20);
		exit(EXIT_FAILURE);
	}
	cmd = split_option(av);
	s = ft_strstr(env, "PATH=");
	path = ft_split(s, ':');
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		return ((*arg).path = cmd[0], ft_free(path), cmd);
	else
		return (find_path(arg, path, cmd));
	return (ft_free(path), cmd);
}
