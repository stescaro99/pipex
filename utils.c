/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:18:31 by stescaro          #+#    #+#             */
/*   Updated: 2024/02/06 11:28:13 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_fail(int pid, char *err, int fd[2])
{
	if (pid >= 0)
		return ;
	ft_perror(err);
	close(fd[0]);
	close(fd[1]);
	exit (1);
}

int	ft_free(char *s)
{
	free(s);
	return (1);
}

int	ft_perror(char *s)
{
	perror(s);
	return (1);
}

static	char	*get_env_path(char **env)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		s = ft_substr(env[i], 0, j);
		if (!s)
			return (NULL);
		if (ft_strncmp(s, "PATH", 4) == 0)
		{
			free(s);
			return (env[i] + j + 1);
		}
		free(s);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(get_env_path(env), ':');
	if (!allpath)
		return (NULL);
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd && ft_freesplit(allpath))
		return (NULL);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0 && ft_freesplit(s_cmd)
			&& ft_freesplit(allpath))
			return (exec);
		free(exec);
	}
	(void)(ft_freesplit(allpath) + ft_freesplit(s_cmd));
	return (cmd);
}
