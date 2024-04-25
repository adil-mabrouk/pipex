/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fun2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:26:17 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/18 11:19:53 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	free_all(t_data arg)
{
	free(arg.path1);
	free(arg.path2);
	ft_free(arg.cmd1);
	ft_free(arg.cmd2);
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
