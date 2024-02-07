/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:53 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/07 16:10:37 by rboudwin         ###   ########.fr       */
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
char *check_command(char *cmd, char **paths)
{
	int	i;
	char	*ptr_parking;

	i = 0;
	//figure out a way to separate parameters from cmd. 
	//then check the cmd paths.
	char *potential_cmd;	
	while (paths[i])
	{
		potential_cmd = ft_strjoin(paths[i], "/");
		ptr_parking = potential_cmd;
		potential_cmd = ft_strjoin(potential_cmd, cmd);
		free(ptr_parking);

	
		if (potential_cmd)
		{ 
		//	ft_printf("potential_cmd is now: %s\n", potential_cmd);
			if (access(potential_cmd, X_OK) == -1)
			{
				free(potential_cmd);
				i++;
			}
			else
				return (potential_cmd);
		}
	}
	return (NULL);
}
int	validate_arguments(t_pipex *p)
{
	p->input = open(p->argv[1], O_RDONLY);
	if (p->input == -1)
	{
		perror("Failed to open file");
		exit(-1);
	}
	p->cmd1 = check_command(p->argv[2], p->paths);
	p->cmd2 = check_command(p->argv[3], p->paths);
	if (!p->cmd1 || !p->cmd2)
	{
		ft_putstr_fd("Command not found in available paths\n", 2);
		return (0);
	}
	//ft_printf("final correct path is %s\n", p->cmd1);
	//this seems unnecessary, as the above perror will 
	//also report Permission denied as appropriate
	//if (access(argv[1], R_OK) == -1)
	//	perror("Not authorized to read");
	
	//ft_printf("a is now %d\n", a);
	return (1);
}

void	free_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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
	p.argc = argc;
	p.argv = argv;
	p.env = env;
	p.paths = parse_paths(env);
	//while (p.paths[i])
	//	ft_printf("%s\n", p.paths[i++]);
	validate_arguments(&p);
	if (!p.cmd1 || !p.cmd2)
	{	
		free_2d(p.paths);
		return (-1);
	}
	// free paths
	free_2d(p.paths);
}
