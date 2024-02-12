/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:30:41 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/12 13:34:11 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			paths = ft_split(env[i] + 5, ':');
		i++;
	}
	return (paths);
}

char	*check_command(char *cmd, char **paths)
{
	int		i;
	char	*ptr_parking;
	char	*potential_cmd;

	i = 0;
	while (paths[i])
	{
		potential_cmd = ft_strjoin(paths[i], "/");
		ptr_parking = potential_cmd;
		potential_cmd = ft_strjoin(potential_cmd, cmd);
		free(ptr_parking);
		if (potential_cmd)
		{
			if (access(potential_cmd, X_OK) == -1)
			{
				free(potential_cmd);
				i++;
			}
			else
			{
				return (potential_cmd);
			}
		}
	}
	return (NULL);
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

int	check_both_commands(t_pipex *p)
{
	p->cmd_with_path[0] = check_command(p->cmd1[0], p->paths);
	if (!p->cmd_with_path[0])
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(p->cmd1[0], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	p->cmd_with_path[1] = check_command(p->cmd2[0], p->paths);
	if (!p->cmd_with_path[1])
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(p->cmd2[0], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (1);
}

int	validate_arguments(t_pipex *p)
{
	char	*error_str;

	p->input = open(p->argv[1], O_RDONLY);
	if (p->input == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->argv[1], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	if (check_both_commands(p) == -1)
		return (-1);
	return (check_output_file(p));
}