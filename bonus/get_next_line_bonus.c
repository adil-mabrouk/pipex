/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:32:44 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/25 16:21:22 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

char	*ft_get_next(char *var)
{
	char	*string;
	int		i;

	i = 0;
	if (!var)
		return (free(var), var = NULL, NULL);
	while (var[i] != '\n' && var[i])
		i++;
	if (var[i] == '\n')
		i++;
	string = ft_strdup(var + i);
	return (free(var), string);
}

char	*ft_get_line(char *var)
{
	char	*line;
	int		i;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] && var[i] != '\n')
		i++;
	if (var[i] == '\n')
		i++;
	line = ft_substr(var, 0, i);
	return (line);
}

char	*ft_read(int fd, char *buffer, char *var)
{
	int	r_bytes;

	r_bytes = 1;
	while (r_bytes > 0 && !ft_strchr(var, '\n'))
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
			return (free(var), free(buffer), buffer = NULL, var = NULL, NULL);
		buffer[r_bytes] = '\0';
		var = ft_strjoin(var, buffer);
	}
	free(buffer);
	if (var && var[0] == 0)
		return (free(var), var = NULL, NULL);
	return (var);
}

char	*get_next_line(int fd)
{
	static char	*var;
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (free(var), var = NULL, NULL);
	var = ft_read(fd, buffer, var);
	if (!var)
		return (NULL);
	line = ft_get_line(var);
	if (!line)
	{
		free(var);
		var = NULL;
	}
	var = ft_get_next(var);
	return (line);
}
