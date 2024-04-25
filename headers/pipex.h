/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers/pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:44:38 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/15 15:53:38 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PIPEX_H)
#define PIPEX_H

#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef struct s_data
{
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
	char	*fdin;
	char	*fdout;
}		t_data;

char	**ft_parsing(t_data *arg, char *av, char **env, int *info);
char	**ft_split(char *s, char sep);
char	**split_option(char *s);
char	*ft_strdup(char *s);
int		ft_strlen_of_2(char *s1, char *s2);
void	ft_free(char **s);
void	free_all(t_data arg);

#endif
