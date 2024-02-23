/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:53 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/23 13:30:10 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	empty_check(char **argv)
{
	if (!argv[1][0] && !argv[4][0])
	{
		ft_putstr_fd("no such file or directory:\n", 2);
		ft_putstr_fd("no such file or directory:\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!argv[1][0] || !argv[4][0])
	{
		ft_putstr_fd("no such file or directory:\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!argv[2][0] && !argv[3][0])
	{
		ft_putstr_fd("command not found:\n", 2);
		ft_putstr_fd("command not found:\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!argv[2][0] || !argv[3][0])
	{
		ft_putstr_fd("command not found:\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	check_arg_count(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("ERROR: exactly four arguments required\n", 2);
		exit(EXIT_FAILURE);
	}
	empty_check(argv);
}

void	open_output(t_pipex *p)
{
	char	*error_str;

	p->output = open(p->argv[4], O_DIRECTORY);
	if (p->output != -1)
	{
		ft_putstr_fd("is a directory: ", 2);
		ft_putstr_fd(p->argv[4], 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	p->output = open(p->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (p->output == -1)
	{
		error_str = strerror(errno);
		ft_putstr_fd(error_str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(p->argv[4], 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
}

void	init_p(t_pipex *p, int argc, char **argv, char **env)
{
	check_arg_count(argc, argv);
	p->argc = argc;
	p->argv = argv;
	p->env = env;
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
	if (check_both_commands(&p) == -1 || pipex(&p) <= 0)
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
