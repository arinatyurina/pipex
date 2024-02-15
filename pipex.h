/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:01:43 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/13 14:41:06 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct s_data
{
	int		in;
	int		out;
	int		**pipefd;
	char	**paths;
	char	*path;
	char	**cmd;
	int		pipes_nbr;
	int		ex;
	int		i;
	int		id;
}	t_data;

char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_three(char const *s1, char ch, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);

void	check_path(t_data *vars, char **envp);
void	checking_access(t_data *vars, char **envp);
void	check_argc(int argc);
void	check_file_one(t_data *vars, char **argv);

void	create_pipes(t_data *vars, int argc);
void	redirect_stream(int input, int output);
void	closing_pipes(t_data *vars);
void	free_pipes(t_data *vars);

void	perror_exit(char *message, int n);
void	free_cmd(t_data *vars);
void	free_all(t_data *vars);

#endif
