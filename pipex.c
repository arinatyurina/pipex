/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:56:48 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/13 18:12:02 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// < file1 cmd1 | cmd2 > file2
/* The general idea: we read from infile, 
execute cmd1 with infile as input, 
send the output to cmd2, 
which will write to outfile. */

#include "pipex.h"

void	if_path_null(t_data *vars, char **argv, int argc)
{
	if (vars->path == NULL)
	{
		perror(vars->cmd[0]);
		vars->out = open(argv[argc - 1],
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		close(vars->out);
		free_cmd(vars);
		free_pipes(vars);
		exit (127);
	}
}

void	first_cmd(t_data *vars, char **argv, char **envp, int argc)
{
	vars->in = open(argv[1], O_RDONLY);
	if (vars->in == -1)
	{
		free_all(vars);
		perror_exit(argv[1], 127);
	}
	if_path_null(vars, argv, argc);
	redirect_stream(vars->in, vars->pipefd[0][1]);
	closing_pipes(vars);
	if (execve(vars->path, vars->cmd, envp) == -1)
		perror_exit(vars->path, 1);
}

void	child_process(t_data *vars, int argc, char **argv, char **envp)
{
	if (vars->i == 0)
		first_cmd(vars, argv, envp, argc);
	else if (vars->i == argc - 4)
	{
		vars->out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (vars->out == -1)
		{
			free_all(vars);
			perror_exit(argv[argc - 1], 127);
		}
		if_path_null(vars, argv, argc);
		redirect_stream(vars->pipefd[vars->i - 1][0], vars->out);
		closing_pipes(vars);
		if (execve(vars->path, vars->cmd, envp) == -1)
			perror_exit(vars->path, 1);
	}
	else
	{
		if_path_null(vars, argv, argc);
		redirect_stream(vars->pipefd[vars->i - 1][0], vars->pipefd[vars->i][1]);
		closing_pipes(vars);
		if (execve(vars->path, vars->cmd, envp) == -1)
			perror_exit(vars->path, 1);
	}
}

void	forking(t_data *vars, int argc, char **argv, char **envp)
{
	vars->i = 0;
	while (vars->i < (argc - 3))
	{
		vars->id = fork();
		if (vars->id == -1)
			perror_exit("Error while forking", 1);
		if (vars->id == 0)
		{
			vars->cmd = ft_split(argv[2 + vars->i], ' ');
			if (vars->cmd == NULL)
				perror_exit("Error splitting command", 1);
			checking_access(vars, envp);
			child_process(vars, argc, argv, envp);
		}
		vars->i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	vars;
	int		wstatus;

	check_argc(argc);
	check_file_one(&vars, argv);
	create_pipes(&vars, argc);
	forking(&vars, argc, argv, envp);
	closing_pipes(&vars);
	free_pipes(&vars);
	if (vars.id != 0 && vars.ex != 127)
	{
		waitpid(vars.id, &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit(WEXITSTATUS(wstatus));
	}
	return (vars.ex);
}
