/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:18:20 by stescaro          #+#    #+#             */
/*   Updated: 2024/02/06 11:29:37 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

int		ft_freesplit(char **s);
int		ft_perror(char *s);
char	*get_path(char *cmd, char **env);
int		ft_free(char *s);
void	fork_fail(int pid, char *err, int fd[2]);

#endif
