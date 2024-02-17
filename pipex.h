/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:58 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/17 15:33:51 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "Libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/errno.h>
# include <string.h>

typedef struct s_pipex
{
	int		input;
	int		output;
	int		rd_pipe;
	int		wr_pipe;
	int		argc;
	char	**cmd1;
	char	**cmd2;
	char	**cmd_with_path;
	char	*cmd1_parking;
	char	*cmd2_parking;
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
#endif