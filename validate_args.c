/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:30:41 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/23 13:19:25 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			if (access(potential_cmd, F_OK) == -1)
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

void	find_command_path_1(t_pipex *p)
{
	char	*error_str;

	p->cmd_with_path[0] = check_command(p->cmd1[0], p->paths);
	if (!p->cmd_with_path[0])
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(p->cmd1[0], 2);
		ft_putchar_fd('\n', 2);
	}
	else if (access(p->cmd_with_path[0], X_OK) == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->cmd1[0], 2);
		ft_putchar_fd('\n', 2);
	}
}

void	find_command_path_2(t_pipex *p)
{
	char	*error_str;

	p->cmd_with_path[1] = check_command(p->cmd2[0], p->paths);
	if (!p->cmd_with_path[1])
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(p->cmd2[0], 2);
		ft_putchar_fd('\n', 2);
	}
	else if (access(p->cmd_with_path[1], X_OK) == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->cmd2[0], 2);
		ft_putchar_fd('\n', 2);
	}
}

int	check_both_commands(t_pipex *p)
{
	if (ft_strchr(p->cmd1[0], '/'))
	{
		if (absolute_path_handler_1(p) == -1)
			return (-1);
	}
	else
		find_command_path_1(p);
	if (ft_strchr(p->cmd2[0], '/'))
	{
		if (absolute_path_handler_2(p) == -1)
			return (-1);
	}
	else
	{
		find_command_path_2(p);
	}
	return (1);
}
