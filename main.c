/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:53 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/12 12:32:20 by rboudwin         ###   ########.fr       */
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
			//	free(cmd);
				return (potential_cmd);
			}
		}
	}
//	free(cmd);
	return (NULL);
}

int	validate_arguments(t_pipex *p)
{
	char *error_str;

	p->input = open(p->argv[1], O_RDONLY);
	if (p->input == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->argv[1], 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	//this probably leaks
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
	if (access(p->argv[4], F_OK) == 0)
	{
		p->output = open(p->argv[4], O_WRONLY);
		if (p->output == -1)
		{
			perror("Output file cannot be opened");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_pipex	p;

	i = 0;
	if (argc != 5)
	{
		ft_putstr_fd("ERROR: exactly four arguments required\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0])
	{
		ft_putstr_fd("ERROR: empty string detected\n", 2);
		exit(EXIT_FAILURE);
	}
	p.argc = argc;
	p.argv = argv;
	p.env = env;
	p.cmd1 = ft_split(argv[2], ' ');
	p.cmd2 = ft_split(argv[3], ' ');
	p.paths = parse_paths(env);
	p.output = 1;
	p.cmd_with_path = malloc(sizeof(char *) * (argc - 2));
	if (p.cmd_with_path == NULL)
	{
		free_2d(p.paths);
		free_2d(p.cmd1);
		free_2d(p.cmd2);
		exit(EXIT_FAILURE);
	}
	if (validate_arguments(&p) == -1)
	{
		//free(p.cmd1_parking);
	//	free(p.cmd2_parking);
		free_2d(p.paths);
		free_2d(p.cmd1);
		free_2d(p.cmd2);
		free_2d(p.cmd_with_path);
		exit(EXIT_FAILURE);
	}
	
	//free(p.cmd1_parking);
	//free(p.cmd2_parking);
	//if we get here we must have two valid commands,
	//and the input file exists and has the appropriate permissions
	//and the output file either does not yet exist, or if it does,
	//it has write permissions.
	if (pipex(&p) < 0)
	{
		free_2d(p.paths);
		free_2d(p.cmd1);
		free_2d(p.cmd2);
		free_2d(p.cmd_with_path);
		exit(EXIT_FAILURE);
	}
	//ft_printf("We have exited pipex function\n");
	free_2d(p.paths);
	free_2d(p.cmd1);
	free_2d(p.cmd2);
	free_2d(p.cmd_with_path);
	//ft_printf("Execute victory dance protocol\n");
	exit(EXIT_SUCCESS);
}
