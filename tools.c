/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:27:28 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/23 13:19:13 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	check_output_file(t_pipex *p)
{
	char	*error_str;

	if (access(p->argv[4], F_OK) == 0)
	{
		p->output = open(p->argv[4], O_WRONLY);
		if (p->output == -1)
		{
			error_str = strerror(errno);
			ft_putstr_fd(error_str, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(p->argv[4], 2);
			ft_putchar_fd('\n', 2);
			return (-1);
		}
	}
	return (1);
}

char	**parse_paths(char **env)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			paths = ft_split(env[i] + 5, ':');
		i++;
	}
	return (paths);
}

int	absolute_path_handler_1(t_pipex *p)
{
	char	*error_str;

	if (access(p->cmd1[0], F_OK) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(p->cmd1[0], 2);
		ft_putchar_fd('\n', 2);
	}
	else if (access(p->cmd1[0], X_OK) == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->cmd1[0], 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		p->cmd_with_path[0] = ft_strdup(p->cmd1[0]);
		if (!p->cmd_with_path[0])
			return (-1);
	}
	return (1);
}

int	absolute_path_handler_2(t_pipex *p)
{
	char	*error_str;

	if (access(p->cmd2[0], F_OK) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(p->cmd2[0], 2);
		ft_putchar_fd('\n', 2);
	}
	else if (access(p->cmd2[0], X_OK) == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->cmd2[0], 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		p->cmd_with_path[1] = ft_strdup(p->cmd2[0]);
		if (!p->cmd_with_path[1])
			return (-1);
	}
	return (1);
}
