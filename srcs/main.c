/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:49:09 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/25 21:03:50 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	read_command(char *argv[], char *envp[], t_pipex *data)
{
	char	*path;
	int		infile;
	char	**cmd;

	close(data->fd[0]);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		exit_error(argv[1], NULL, EXIT_FAILURE);
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		exit_error("Malloc error.\n", NULL, EXIT_FAILURE);
	if (dup2(infile, STDIN_FILENO) == -1)
		exit_error("Failed to redirect infile to stdin.", cmd, EXIT_FAILURE);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		exit_error("Failed to redirect fd[1] to stdout.", cmd, EXIT_FAILURE);
	path = get_program_path(cmd[0], envp);
	if (!path)
		exit_program_not_found(cmd, data->fd[1], data->outfile);
	if (execve(path, cmd, envp))
	{
		free(path);
		exit_error(NULL, cmd, 127);
	}
}

void	write_command(char *argv[], char *envp[], t_pipex *data)
{
	char	*path;
	char	**cmd;

	close(data->fd[1]);
	data->outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (data->outfile == -1)
		exit_error("Error: Can't open file2.\n", NULL, EXIT_FAILURE);
	cmd = ft_split(argv[3], ' ');
	if (!cmd)
	{
		close(data->outfile);
		exit_error("Malloc error.\n", NULL, EXIT_FAILURE);
	}
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		exit_error("Failed to redirect fd[0] to stdin.", cmd, EXIT_FAILURE);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		exit_error("Failed to redirect outfile to stdout.", cmd, EXIT_FAILURE);
	path = get_program_path(cmd[0], envp);
	if (!path)
		exit_program_not_found(cmd, data->fd[0], data->outfile);
	if (execve(path, cmd, envp))
	{
		free(path);
		exit_error(NULL, cmd, 127);
	}
}

void	start_commands(char *argv[], char *envp[], t_pipex *data)
{
	data->read_pid = fork();
	if (data->read_pid == -1)
		exit_error("Can't fork the process.", NULL, EXIT_FAILURE);
	if (data->read_pid == 0)
		read_command(argv, envp, data);
	data->write_pid = fork();
	if (data->write_pid == -1)
		exit_error("Can't fork the process.", NULL, EXIT_FAILURE);
	if (data->write_pid == 0)
		write_command(argv, envp, data);
}

int	wait_commands(t_pipex *data)
{
	int	active;
	int	status;
	int	exit_code;
	int	ret;

	active = 2;
	exit_code = EXIT_SUCCESS;
	status = 0;
	while (active > 0)
	{
		ret = waitpid(0, &status, 0);
		if (ret == -1)
			exit_error("waitpid failed.", NULL, EXIT_FAILURE);
		if (ret == data->read_pid || ret == data->write_pid)
		{
			if (ret == data->write_pid)
				exit_code = WEXITSTATUS(status);
			close(data->fd[0]);
			close(data->fd[1]);
			active--;
		}
	}
	return (exit_code);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	ft_bzero(&data, sizeof(t_pipex));
	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments.\n", STDERR_FILENO);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	if (pipe(data.fd) == -1)
		exit_error("Can't create pipe.", NULL, EXIT_FAILURE);
	start_commands(argv, envp, &data);
	return (wait_commands(&data));
}
