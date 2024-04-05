/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:44:38 by amabrouk          #+#    #+#             */
/*   Updated: 2024/04/05 00:11:22 by amabrouk         ###   ########.fr       */
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

typedef struct s_args
{
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
	int		fdin;
	int		fdout;
}		t_args;

char	*ft_parsing(t_args arg, char *av, char **env);
char	**ft_split(char *s, char sep);
void	ft_free(char **s);

#endif
