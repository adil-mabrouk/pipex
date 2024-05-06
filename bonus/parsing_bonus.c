/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:04:39 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/06 16:00:16 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

int	count_word(char *s, char sep)
{
	int	wc;

	wc = 0;
	while (*s)
	{
		while (*s && *s == sep)
			s++;
		if (*s && *s != sep)
			wc++;
		while (*s && *s != sep)
			s++;
	}
	return (wc);
}

char	*fill_word(char *s, char sep, int *i)
{
	char	*copy;
	int		start;
	int		j;

	while (s[*i] && s[*i] == sep)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != sep)
		(*i)++;
	copy = (char *)malloc(sizeof(char) * ((*i - start) + 1));
	if (!copy)
		return (NULL);
	j = 0;
	while (j < *i - start)
	{
		copy[j] = s[start + j];
		j++;
	}
	copy[j++] = '/';
	copy[j] = 0;
	return (copy);
}

char	**ft_split(char *s, char sep)
{
	char	**res;
	int		wc;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	wc = count_word(s, sep);
	res = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!res)
		return (NULL);
	k = 0;
	i = 0;
	while (k < wc)
	{
		res[k] = fill_word(s, sep, &i);
		if (!res[k])
			return (ft_free(res), NULL);
		k++;
	}
	res[k] = NULL;
	return (res);
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

char	**ft_parsing(t_data *arg, char *av, char **env)
{
	char	*s;
	char	**cmd;
	char	**path;
	int		i;

	if ((av && !av[0]) || is_whitespace(av))
	{
		write(2, "\tcommand not found\n", 19);
		exit(EXIT_FAILURE);
	}
	i = 0;
	cmd = split_option(av);
	s = ft_strstr(env, "PATH=");
	path = ft_split(s, ':');
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		return ((*arg).path = cmd[0], ft_free(path), cmd);
	else
		return (find_path(arg, path, cmd));
	return (perror(NULL), cmd);
}
