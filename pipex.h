/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:58 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/23 13:18:41 by rboudwin         ###   ########.fr       */
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
void	open_output(t_pipex *p);
int		check_both_commands(t_pipex *p);
int		check_output_file(t_pipex *p);
int		absolute_path_handler_1(t_pipex *p);
int		absolute_path_handler_2(t_pipex *p);
#endif