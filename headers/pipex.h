/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:19:06 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/05 11:23:33 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PIPEX_H)
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**cmd;
	char	*path;
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
}		t_data;

char	**ft_parsing(t_data *arg, char *av, char **env);
char	**ft_split(char *s, char sep);
char	**split_option(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
int		ft_strlen_of_2(char *s1, char *s2);
int		ft_strlen(char *s);
void	ft_free(char **s);

#endif
