/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:58 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:48 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "Libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_pipex
{
	int		input;
	int		output;
	int		argc;
	char	**cmd1;
	char	**cmd2;
	char	**cmd_with_path;
	char	**argv;
	char	**env;
	char	**paths;
	int		child1_pid;
	int		child2_pid;
	int		pipefd[2];
}	t_pipex;
void	free_2d(char **arr);
int		pipex(t_pipex *p);
char	**parse_paths(char **env);
int		validate_arguments(t_pipex *p);
void	open_output(t_pipex *p);
#endif