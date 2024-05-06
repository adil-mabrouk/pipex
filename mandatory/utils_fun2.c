/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fun2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:26:17 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/06 16:09:47 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

// void	free_all(t_data arg)
// {
// 	free(arg.path1);
// 	free(arg.path2);
// 	ft_free(arg.cmd1);
// 	ft_free(arg.cmd2);
// }

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

char	*ft_strdup(char *s)
{
	char	*copy;
	int		i;

	if (!*s)
		return (NULL);
	copy = malloc(sizeof(char) * (ft_strlen_of_2(s, NULL) + 1));
	if (!copy)
		return (free(s), NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = 0;
	return (free(s), copy);
}
