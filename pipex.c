/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:50:39 by stescaro          #+#    #+#             */
/*   Updated: 2024/02/06 14:07:47 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	child1(int fd[2], char **argv, char **env)
{
	int		i_fd;
	char	**cmd;
	char	*path;
	int		res;

	close(fd[0]);
	i_fd = open(argv[0], O_RDONLY, 0777);
	if (i_fd < 0)
		return (ft_perror("Error!\nInfile opening failed") + close(fd[1]) + 1);
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(i_fd, 0);
	close(i_fd);
	cmd = ft_split(argv[1], ' ');
	if (!cmd)
		return (ft_perror("Error!\nCmd allocation failed"));
	path = get_path(argv[1], env);
	if (!path)
		return (ft_perror("Error!\nPath alloc. failed") + ft_freesplit(cmd));
	res = execve(path, cmd, env);
	ft_freesplit(cmd);
	if (res < 0)
		return (ft_perror("Error!\nEcecve execution failed"));
	free(path);
	return (0);
}

static	void	child2(int fd[2], char **argv, char **env)
{
	int		o_fd;
	char	**cmd;
	char	*path;
	int		res;

	close(fd[1]);
	o_fd = open(argv[3], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (o_fd < 0)
		exit(ft_perror("Error!\nOutfile opening failed") + close(fd[0]));
	dup2(fd[0], 0);
	dup2(o_fd, 1);
	close(fd[0]);
	close(o_fd);
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		exit(ft_perror("Error!\nCmd allocation failed"));
	path = get_path(argv[2], env);
	if (!path)
		exit(ft_perror("Error!\nPath allocation failed") + ft_freesplit(cmd));
	res = execve(path, cmd, env);
	ft_freesplit(cmd);
	if (res < 0)
		exit(ft_perror("Error!\nExecve execution failed"));
	free(path);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		exit(ft_perror("Error!\nInvalid number of arguments"));
	if (pipe(fd) < 0)
		exit(ft_perror("Error!\nPipe execution failed"));
	pid1 = fork();
	fork_fail(pid1, "Error!\nFork execution failed", fd);
	argc = 0;
	if (pid1 == 0)
		argc = child1(fd, &argv[1], env);
	if (pid1 == 0)
		waitpid(pid1, NULL, 0);
	if (argc != 0)
		return (1);
	pid2 = fork();
	fork_fail(pid2, "Error!\nFork execution failed", fd);
	if (pid2 == 0)
		child2(fd, &argv[1], env);
	if (pid2 == 0)
		waitpid(pid2, NULL, 0);
	return (close(fd[0]) + close(fd[1]));
}
