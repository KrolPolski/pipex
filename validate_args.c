/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:30:41 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/23 12:53:21 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	char *error_str;
	//add a check looking for a /, add alternate path to check just one place
	if (ft_strchr(p->cmd1[0], '/'))
	{
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
	}
	else
	{
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
	if (ft_strchr(p->cmd2[0], '/'))
	{
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
	}

	else 
	{
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
	//should we even be returning values here?
	return (1);
}
