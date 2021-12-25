/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:13:37 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/25 21:13:43 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

static void	ft_freetab(char **tab)
{
	short int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	exit_program_not_found(char **cmd, int fd, int file)
{
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_freetab(cmd);
	close(fd);
	close(file);
	exit(127);
}

void	exit_error(char *err, char **tab, int code)
{
	if (err)
		perror(err);
	if (tab)
		ft_freetab(tab);
	exit(code);
}

static char	*check_paths(char *cmd, char **paths)
{
	int		i;
	char	*tmp_path;
	char	*path;

	path = NULL;
	i = 0;
	while (paths[i] != NULL)
	{
		tmp_path = ft_strjoin(paths[i], "/");
		if (!tmp_path)
			exit_error("malloc error", paths, EXIT_FAILURE);
		path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!path)
			exit_error("malloc error", paths, EXIT_FAILURE);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_program_path(char *cmd, char *envp[])
{
	short int	i;
	char		*path;
	char		**paths;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	paths = ft_split(&envp[i][5], ':');
	if (!paths)
		exit_error("malloc error", NULL, EXIT_FAILURE);
	path = check_paths(cmd, paths);
	ft_freetab(paths);
	return (path);
}
