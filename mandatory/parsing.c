/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:04:39 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/26 17:00:45 by amabrouk         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen_of_2(s1, s2);
	joined = malloc(sizeof(char) * len + 1);
	if (!joined)
		return (NULL);
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = 0;
	return (joined);
}

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

char	**ft_parsing(t_data *arg, char *av, char **env, int *info)
{
	char	*s;
	char	**cmd;
	char	**path;
	char	*joined;
	int		i;

	i = 0;
	joined = NULL;
	if (av && !av[0])
		return (write(2, "error\n", 6), exit(1), NULL);
	cmd = split_option(av);
	s = ft_strstr(env, "PATH=");
	path = ft_split(s, ':');
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
	{
		while (path[i])
		{
			joined = ft_strjoin(path[i], cmd[0]);
			if (joined && access(joined, F_OK) == 0)
			{
				if (*info == 1)
					(*arg).path1 = ft_strdup(joined);
				if (*info == 2)
					(*arg).path2 = ft_strdup(joined);
				return (ft_free(path), cmd);
			}
			i++;
		}
		free(joined);
	}
	return (ft_free(path), cmd);
}
