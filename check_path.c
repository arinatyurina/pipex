/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:08:12 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/13 18:12:42 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_path(t_data *vars, char **envp)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	vars->paths = ft_split(envp[i] + 5, ':');
	j = 0;
	while (vars->paths[j] != NULL)
	{
		path = ft_strjoin_three(vars->paths[j], '/', vars->cmd[0]);
		if (access(path, X_OK) == -1)
		{
			j++;
			free(path);
		}
		else
		{
			vars->path = path;
			return ;
		}
	}
	vars->path = NULL;
	return ;
}

static int	found_sl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	checking_access(t_data *vars, char **envp)
{
	int	i;

	i = 0;
	if (access(vars->cmd[0], X_OK) != -1 || found_sl(vars->cmd[0]) == 1)
	{
		vars->path = vars->cmd[0];
		return ;
	}
	else
	{
		check_path(vars, envp);
		while (vars->paths[i] != NULL)
		{
			free(vars->paths[i]);
			i++;
		}
		free(vars->paths);
	}
	return ;
}

void	check_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments", STDERR_FILENO);
		exit(1);
	}
}

void	check_file_one(t_data *vars, char **argv)
{
	int	file;

	vars->ex = 0;
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		vars->ex = 1;
	close(file);
}
