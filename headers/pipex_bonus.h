/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:04:10 by amabrouk          #+#    #+#             */
/*   Updated: 2024/05/05 16:08:46 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PIPEX_BONUS_H)
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_data
{
	char	**cmd;
	char	*path;
	int		fdin;
	int		fdout;
	char	*infile;
	char	*outfile;
	int		ac;
	int		iter;
}		t_data;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

void	pipex(t_data arg, char **av, char **env);
char	**ft_parsing(t_data *arg, char *av, char **env);
char	**find_path(t_data *arg, char **path, char **cmd);
int		ft_strlen_of_2(char *s1, char *s2);
char	**ft_split(char *s, char sep);
char	**split_option(char *s);
char	*ft_strdup(char *s);
int		is_whitespace(char *s);
void	ft_free(char **s);
int		ft_strcmp_nl(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
int		ft_strlen(char *s);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char	*s);

#endif
