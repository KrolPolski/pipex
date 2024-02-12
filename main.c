/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:53 by rboudwin          #+#    #+#             */
/*   Updated: 2024/02/12 13:32:47 by rboudwin         ###   ########.fr       */
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
		//consider that this error doesn't match shell behavior
		ft_putstr_fd("ERROR: empty string detected\n", 2);
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
		//consider what to free here and if we need an error msg
		exit(EXIT_FAILURE);
	}
	p->paths = parse_paths(env);
	if (!p->paths)
	{
		free_2d(p->cmd1);
		free_2d(p->cmd2);
		exit(EXIT_FAILURE);
	}
	p->output = 1;
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
