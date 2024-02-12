/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:53 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/12 15:17:05 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_arg_count(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("ERROR: exactly four arguments required\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0])
	{
		ft_putstr_fd("no such file or directory:\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	open_output(t_pipex *p)
{
	p->output = open(p->argv[4], O_DIRECTORY);
	if (p->output != -1)
	{
		ft_putstr_fd("is a directory: ", 2);
		ft_putstr_fd(p->argv[4], 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	p->output = open(p->argv[4], O_CREAT | O_WRONLY, 0666);
	if (p->output == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
}

void	init_p(t_pipex *p, int argc, char **argv, char **env)
{
	check_arg_count(argc, argv);
	p->argc = argc;
	p->argv = argv;
	p->env = env;
	open_output(p);
	p->cmd1 = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	if (!p->cmd1 || !p->cmd2)
	{
		if (p->cmd1)
			free_2d(p->cmd1);
		exit(EXIT_FAILURE);
	}
	p->paths = parse_paths(env);
	if (!p->paths)
	{
		free_2d(p->cmd1);
		free_2d(p->cmd2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;

	init_p(&p, argc, argv, env);
	p.cmd_with_path = malloc(sizeof(char *) * (argc - 2));
	if (p.cmd_with_path == NULL)
	{
		free_2d(p.paths);
		free_2d(p.cmd1);
		free_2d(p.cmd2);
		exit(EXIT_FAILURE);
	}
	if (validate_arguments(&p) == -1 || pipex(&p) < 0)
	{
		free_2d(p.paths);
		free_2d(p.cmd1);
		free_2d(p.cmd2);
		free_2d(p.cmd_with_path);
		exit(EXIT_FAILURE);
	}
	free_2d(p.paths);
	free_2d(p.cmd1);
	free_2d(p.cmd2);
	free_2d(p.cmd_with_path);
	exit(EXIT_SUCCESS);
}
