/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:14 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/13 14:41:56 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(char *message, int n)
{
	perror(message);
	exit(n);
}

void	create_pipes(t_data *vars, int argc)
{
	int	i;

	vars->pipes_nbr = argc - 4;
	vars->pipefd = (int **)malloc((vars->pipes_nbr) * sizeof(int *));
	if (!vars->pipefd)
		perror_exit("Malloc error", 1);
	i = 0;
	while (i < vars->pipes_nbr)
	{
		vars->pipefd[i] = (int *)malloc(2 * sizeof(int));
		if (pipe(vars->pipefd[i]) == -1)
			perror_exit("Error while creating a pipe", 1);
		i++;
	}
}

void	redirect_stream(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
}

void	closing_pipes(t_data *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipes_nbr)
	{
		close(vars->pipefd[i][0]);
		close(vars->pipefd[i][1]);
		i++;
	}
}

void	free_pipes(t_data *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipes_nbr)
	{
		free(vars->pipefd[i]);
		i++;
	}
	free(vars->pipefd);
}
