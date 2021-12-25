/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:20:39 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/25 21:52:19 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex {
	int		read_pid;
	int		write_pid;
	int		fd[2];
	int		infile;
	int		outfile;
}	t_pipex;

void	exit_program_not_found(char **cmd, int fd, int file);
void	read_command(char *argv[], char *envp[], t_pipex *data);
void	write_command(char *argv[], char *envp[], t_pipex *data);
void	exit_error(char *err, char **tab, int code);
char	*get_program_path(char *cmd, char *envp[]);

#endif