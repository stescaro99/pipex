/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:55:42 by stescaro          #+#    #+#             */
/*   Updated: 2024/02/06 13:58:26 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	int	read_gnl(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = ft_strdup(buffer);
	if (!(*line))
		return (free(buffer), -1);
	free(buffer);
	return (r);
}

static	int	do_command(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (1);
	path = get_path(cmd[0], env);
	if (!path)
		return (ft_freesplit(cmd));
	if (execve(path, cmd, env) < 0)
		return (ft_freesplit(cmd));
	return (free(path), ft_freesplit(cmd) - 1);
}

static	void	child(char *argv, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(ft_perror("Error!\nPipe execution failed"));
	pid = fork();
	if (pid == -1)
		exit(ft_perror("Error!\nFork execution failed")
			+ close(fd[1]) + close(fd[0]));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		if (do_command(argv, env))
			exit(ft_perror("Error!\nExecve failed"));
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

static	void	here_doc(char *lmt)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		exit(ft_perror("Error!\nPipe execution failed"));
	pid = fork();
	if (pid < 0)
		exit(ft_perror("Error!\nFork execution failed"));
	if (pid == 0 && !close(fd[0]))
	{
		while (write(1, "pipe heredoc> ", 14) && read_gnl(&line))
		{
			if (ft_strncmp(line, lmt, ft_strlen(lmt)) == 0
				&& line[ft_strlen(lmt)] == '\n')
				exit(close(fd[1]) + ft_free(line));
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		dup2(fd[0], close(fd[1]));
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	i_fd;
	int	o_fd;

	if (argc < 5)
		exit(ft_perror("Error!\nNot enough arguments"));
	i = 2;
	o_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (o_fd < 0)
		exit(ft_perror("Error!\nOutput open failed"));
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0 && argc == 6 && ++i)
		here_doc(argv[2]);
	else
	{
		i_fd = open(argv[1], O_RDONLY, 0777);
		if (i_fd < 0)
			return (perror("Error!\nInput open failed"), close(o_fd) + 1);
		dup2(i_fd, 0);
	}
	while (i < argc - 2)
		child(argv[i++], env);
	dup2(o_fd, 1);
	if (do_command(argv[argc - 2], env))
		return (perror("Error!\nExecve failed"), close(i_fd) + close(o_fd) + 1);
	return (close(i_fd) + close(o_fd));
}
