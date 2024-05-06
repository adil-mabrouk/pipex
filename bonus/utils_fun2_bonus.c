/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fun2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:26:17 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/05 15:38:57 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

// void	free_all(t_data arg)
// {
	// free(arg.path1);
	// free(arg.path2);
	// ft_free(arg.cmd1);
	// ft_free(arg.cmd2);
// }

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
			return (cmd);
		}
		i++;
	}
	return (cmd);
}

int	is_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (i == ft_strlen(s))
		return (1);
	return (0);
}

int	ft_strcmp_nl(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == 0 && s2[i] && s2[i] == '\n')
		return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
