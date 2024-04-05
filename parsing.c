/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:04:39 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/05 00:15:12 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen_of_2s(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	while (*s2 && *s2 != ' ' && *s2 != '\t')
	{
		s2++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, char sep)
{
	char	*joined;
	int		i;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen_of_2s(s1, s2) + 1;
	joined = malloc(sizeof(char) * len + 1);
	if (!joined)
		return (NULL);
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	joined[i] = sep;
	while (*s2 && *s2 != ' ' && *s2 != '\t')
		joined[++i] = *s2++;
	joined[++i] = 0;
	return (joined);
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
	wc = word_count(s, sep);
	res = (char **)malloc(sizeof(char *) * 9);
	if (!res)
		return (NULL);
	k = 0;
	i = 0;
	while (k < 8)
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

char	*ft_parsing(t_args arg, char *av, char **env)
{
	char	*s;
	char	**path;
	char	*joined;
	char	*command;
	int		i;

	i = 0;
	s = ft_strstr(env, "PATH=");
	path = ft_split(s, ':');
	command = ft_split(av[2], ' ');
	while (path[i])
	{
		joined = ft_strjoin(path[i], command[0], '/');
		if (joined && access(joined, F_OK) == 0)
			return (ft_free(path), joined);
		free(joined);
		i++;
	}
	return (ft_free(path), NULL);
}
